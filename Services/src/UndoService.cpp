#include "../UndoService.hpp"

#include <iostream>

#include "../CoachService.hpp"
#include "../NetworkService.hpp"
#include "../SchedulingService.hpp"
#include "../TrainService.hpp"

UndoService::UndoService(TrainService* ts, CoachService* cs, NetworkService* ns,
                         SchedulingService* ss, LoggerService* ls)
    : trainService(ts),
      coachService(cs),
      networkService(ns),
      schedulingService(ss),
      isUndoingRedoing(false),
      loggerService(ls)
{
}

std::string UndoService::getActionName(ActionType type) const
{
    switch (type)
    {
        case ActionType::REGISTER_TRAIN:
            return "REGISTER_TRAIN";
        case ActionType::REMOVE_TRAIN:
            return "REMOVE_TRAIN";
        case ActionType::CREATE_COACH:
            return "CREATE_COACH";
        case ActionType::DELETE_COACH:
            return "DELETE_COACH";
        case ActionType::LINK_COACH:
            return "LINK_COACH";
        case ActionType::UNLINK_COACH:
            return "UNLINK_COACH";
        case ActionType::REVERSE_TRAIN:
            return "REVERSE_TRAIN";
        case ActionType::CREATE_STATION:
            return "CREATE_STATION";
        case ActionType::DELETE_STATION:
            return "DELETE_STATION";
        case ActionType::LINK_STATIONS:
            return "LINK_STATIONS";
        case ActionType::UNLINK_STATIONS:
            return "UNLINK_STATIONS";
        case ActionType::BOOK_SEAT:
            return "BOOK_SEAT";
        case ActionType::CANCEL_SEAT:
            return "CANCEL_SEAT";
        case ActionType::ASSIGN_ROUTE:
            return "ASSIGN_ROUTE";
        default:
            return "UNKNOWN_ACTION";
    }
}

UndoService::~UndoService()
{
    while (!undoStack.isEmpty()) delete undoStack.pop();
    while (!redoStack.isEmpty()) delete redoStack.pop();
}

void UndoService::recordAction(ActionType type, int primaryId, int secondaryId,
                               const std::string& stringData, int intData, int intData2)
{
    if (isUndoingRedoing) return;

    // Initialize the struct using standard member assignment
    UndoAction* action = new UndoAction();
    action->type = type;
    action->primaryId = primaryId;
    action->secondaryId = secondaryId;
    action->stringData = stringData;
    action->intData = intData;
    action->intData2 = intData2;

    // === NEW SNAPSHOT LOGIC ===
    if (type == ActionType::REMOVE_TRAIN)
    {
        Train* train = trainService->findTrain(primaryId);
        if (train)
        {
            // Save the reverse state into intData2
            action->intData2 = train->getIsReversed() ? 1 : 0;

            // Save logical coach IDs
            action->savedCoachIds = new CircularDoublyLinkedList<int>();
            auto coaches = train->getCoaches();
            if (coaches && !coaches->isEmpty())
            {
                bool rev = train->getIsReversed();
                for (int i = 0; i < coaches->size(); ++i)
                {
                    int idx = rev ? (coaches->size() - 1 - i) : i;
                    action->savedCoachIds->addEnd(coaches->getAt(idx)->getId());
                }
            }

            // 2. Snapshot the Booked Seats
            action->savedBookedSeats = new CircularDoublyLinkedList<int>();
            auto chart = train->getSeatingChart();
            if (chart)
            {
                // Capture the action pointer so the lambda can write to it
                chart->traverseInOrder(
                    [action](Seat::GlobalSeatNumber sNum, Seat* seat)
                    {
                        if (seat->getStatus() == SeatStatus::Booked)
                        {
                            action->savedBookedSeats->addEnd(sNum);
                        }
                    });
            }
        }
    }

    undoStack.push(action);

    while (!redoStack.isEmpty())
    {
        delete redoStack.pop();
    }
}

void UndoService::executeAction(UndoAction* action, bool isUndo)
{
    isUndoingRedoing = true;

    switch (action->type)
    {
        case ActionType::REGISTER_TRAIN:
            if (isUndo)
                trainService->removeTrain(action->primaryId);
            else
                trainService->rehydrateTrain(action->primaryId, action->stringData);

            break;

        case ActionType::REMOVE_TRAIN:
            if (isUndo)
            {
                trainService->rehydrateTrain(action->primaryId, action->stringData);

                // RESTORE FLAG before linking coaches
                Train* train = trainService->findTrain(action->primaryId);
                if (train) train->setIsReversed(action->intData2 == 1);

                // 3. Re-book the passengers into their specific seats
                if (action->savedBookedSeats)
                {
                    for (int i = 0; i < action->savedBookedSeats->size(); i++)
                    {
                        coachService->bookSeat(action->primaryId,
                                               action->savedBookedSeats->getAt(i));
                    }
                }
            }
            else
            {
                trainService->removeTrain(action->primaryId);
            }

            break;

        case ActionType::CREATE_COACH:
            if (isUndo)
                coachService->deleteCoach(action->primaryId);
            else
                coachService->rehydrateCoach(action->primaryId, action->stringData,
                                             action->intData);

            break;

        case ActionType::DELETE_COACH:
            if (isUndo)
                coachService->rehydrateCoach(action->primaryId, action->stringData,
                                             action->intData);
            else
                coachService->deleteCoach(action->primaryId);

            break;

        case ActionType::LINK_COACH:
            if (isUndo)
                coachService->unlinkCoach(action->primaryId, action->secondaryId);
            else
                coachService->linkCoach(action->primaryId, action->secondaryId, action->intData);

            break;

        case ActionType::UNLINK_COACH:
            if (isUndo)
                coachService->linkCoach(action->primaryId, action->secondaryId, action->intData);
            else
                coachService->unlinkCoach(action->primaryId, action->secondaryId);
            break;

        case ActionType::REVERSE_TRAIN:
            coachService->reverseTrain(action->primaryId);

            break;

        case ActionType::CREATE_STATION:
            if (isUndo)
                networkService->deleteStation(action->primaryId);
            else
                networkService->rehydrateStation(action->primaryId, action->stringData);

            break;

        case ActionType::DELETE_STATION:
            if (isUndo)
                networkService->rehydrateStation(action->primaryId, action->stringData);
            else
                networkService->deleteStation(action->primaryId);

            break;

        case ActionType::LINK_STATIONS:
            if (isUndo)
                networkService->unlinkStations(action->primaryId, action->secondaryId);
            else
                networkService->linkStations(action->primaryId, action->secondaryId,
                                             action->intData);

            break;

        case ActionType::UNLINK_STATIONS:
            if (isUndo)
                networkService->linkStations(action->primaryId, action->secondaryId,
                                             action->intData);
            else
                networkService->unlinkStations(action->primaryId, action->secondaryId);

            break;

        case ActionType::BOOK_SEAT:
            if (isUndo)
                coachService->cancelBooking(action->primaryId, action->secondaryId);
            else
                coachService->bookSeat(action->primaryId, action->secondaryId);

            break;

        case ActionType::CANCEL_SEAT:
            if (isUndo)
                coachService->bookSeat(action->primaryId, action->secondaryId);
            else
                coachService->cancelBooking(action->primaryId, action->secondaryId);

            break;

        case ActionType::ASSIGN_ROUTE:
            if (isUndo)
                schedulingService->decommissionRoute(action->primaryId);
            else
                schedulingService->assignRoute(action->primaryId, action->secondaryId,
                                               action->intData);

            break;

        default:
            std::cout << "[UndoService] Action type not supported for Undo/Redo yet.\n";

            break;
    }

    std::cout << "[UndoService] " << (isUndo ? "Undid" : "Redid") << " action successfully.\n";

    isUndoingRedoing = false;
}

void UndoService::undo()
{
    if (undoStack.isEmpty())
    {
        std::cout << "[UndoService] Nothing to undo.\n";
        return;
    }
    UndoAction* action = undoStack.pop();
    executeAction(action, true);
    redoStack.push(action);

    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAA";
    // <-- LOG IT!
    loggerService->logAction("UNDO_ACTION",
                             "Reversed: " + getActionName(action->type) +
                                 " (Primary ID: " + std::to_string(action->primaryId) + ")");

    std::cout << "BBBBBBBBBBBBBBBBBBBBBBB";
}

void UndoService::redo()
{
    if (redoStack.isEmpty())
    {
        std::cout << "[UndoService] Nothing to redo.\n";
        return;
    }
    UndoAction* action = redoStack.pop();
    executeAction(action, false);
    undoStack.push(action);

    // <-- LOG IT!
    loggerService->logAction("REDO_ACTION",
                             "Reapplied: " + getActionName(action->type) +
                                 " (Primary ID: " + std::to_string(action->primaryId) + ")");
}
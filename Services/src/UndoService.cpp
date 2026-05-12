#include "../UndoService.hpp"

#include <iostream>

#include "../CoachService.hpp"
#include "../NetworkService.hpp"
#include "../SchedulingService.hpp"
#include "../TrainService.hpp"

UndoService::UndoService(TrainService* ts, CoachService* cs, NetworkService* ns,
                         SchedulingService* ss)
    : trainService(ts),
      coachService(cs),
      networkService(ns),
      schedulingService(ss),
      isUndoingRedoing(false)
{
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

    UndoAction* action =
        new UndoAction{type, primaryId, secondaryId, stringData, intData, intData2};
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
                trainService->rehydrateTrain(action->primaryId, action->stringData);
            else
                trainService->removeTrain(action->primaryId);
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
}

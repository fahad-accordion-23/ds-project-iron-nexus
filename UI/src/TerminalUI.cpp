#include "../TerminalUI.hpp"

#include <iostream>

#include "../../Services/UndoService.hpp"

TerminalUI::TerminalUI(TrainService* ts, CoachService* cs, NetworkService* ns,
                       SchedulingService* ss, LoggerService* ls, UndoService* us)
    : trainService(ts),
      coachService(cs),
      networkService(ns),
      schedulingService(ss),
      loggerService(ls),
      undoService(us),
      running(false)
{
}

TerminalUI::~TerminalUI()
{
}

void TerminalUI::start()
{
    running = true;
    while (running)
    {
        showMainMenu();
    }
}

void TerminalUI::showMainMenu()
{
    std::cout << "\n====================================\n";
    std::cout << "      🚂 THE IRON NEXUS UI 🚂       \n";
    std::cout << "====================================\n";
    std::cout << "1. Train Registry (Module 1)\n";
    std::cout << "2. Coach Management (Module 2)\n";
    std::cout << "3. Railway Network (Module 3)\n";
    std::cout << "4. Seating Chart (Module 4)\n";
    std::cout << "5. Scheduling (Operations)\n";
    std::cout << "6. Operation Logs (Module 5)\n";
    std::cout << "7. System Save/Load\n";
    std::cout << "8. Undo/Redo\n";
    std::cout << "0. Exit\n";
    std::cout << "------------------------------------\n";
    std::cout << "Choice: ";

    int choice = getChoice();
    switch (choice)
    {
        case 1:
            handleTrainMenu();
            break;
        case 2:
            handleCoachMenu();
            break;
        case 3:
            handleNetworkMenu();
            break;
        case 4:
            handleSeatingMenu();
            break;
        case 5:
            handleSchedulingMenu();
            break;
        case 6:
            handleLogsMenu();
            break;
        case 7:
            handlePersistenceMenu();
            break;
        case 8:
            handleUndoRedoMenu();
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Invalid choice!\n";
    }
}

int TerminalUI::getChoice()
{
    int choice;
    if (!(std::cin >> choice))
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return -1;
    }
    return choice;
}

void TerminalUI::handleTrainMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\n--- [Module 1] Train Registry ---\n";
        std::cout << "1. Register New Train\n";
        std::cout << "2. Decommission (Remove) Train\n";
        std::cout << "3. Find Train by ID\n";
        std::cout << "4. List All Trains (Fleet Patrol)\n";
        std::cout << "5. Emergency Stop Command\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Choice: ";

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                std::string name;
                std::cout << "Enter Train Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                int id = trainService->registerTrain(name);
                if (!undoService->isActive())
                {
                    undoService->recordAction(ActionType::REGISTER_TRAIN, id, -1, name);
                }
                loggerService->logAction("TRAIN_REGISTER", "Name: " + name);
                break;
            }
            case 2:
            {
                int id;
                std::cout << "Enter Train ID to remove: ";
                std::cin >> id;
                Train* t = trainService->findTrain(id);
                if (t && !undoService->isActive())
                {
                    undoService->recordAction(ActionType::REMOVE_TRAIN, id, -1, t->getName());
                }
                trainService->removeTrain(id);
                loggerService->logAction("TRAIN_REMOVE", "ID: " + std::to_string(id));
                break;
            }
            case 3:
            {
                int id;
                std::cout << "Enter Train ID to find: ";
                std::cin >> id;
                Train* t = trainService->findTrain(id);
                if (t)
                {
                    std::cout << "[Found] " << t->getName() << " (ID: " << t->getId() << ")\n";
                }
                else
                {
                    std::cout << "Train not found.\n";
                }
                break;
            }
            case 4:
                trainService->listAllTrains();
                break;
            case 5:
            {
                int id;
                std::cout << "Enter Train ID for Emergency Stop: ";
                std::cin >> id;
                trainService->emergencyStop(id);
                loggerService->logAction("EMERGENCY_STOP", "ID: " + std::to_string(id));
                break;
            }
            case 0:
                back = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

void TerminalUI::handleCoachMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\n--- [Module 2] Coach Management ---\n";
        std::cout << "1. Create Standalone Coach\n";
        std::cout << "2. Delete Coach\n";
        std::cout << "3. Link Coach to Train\n";
        std::cout << "4. Unlink Coach from Train\n";
        std::cout << "5. Reverse Train\n";
        std::cout << "6. List All Coaches\n";
        std::cout << "7. Traverse Train (View Linked Coaches)\n";  // <--- ADDED
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                int capacity = 0;  // Initialize to 0 to trigger the while loop
                std::string name;
                std::cout << "Enter Coach Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);

                // --- THE FIX: Input Validation Loop ---
                while (capacity <= 0)
                {
                    std::cout << "Enter Capacity (must be > 0): ";
                    std::cin >> capacity;

                    if (capacity <= 0)
                    {
                        std::cout << "Invalid capacity! Please try again.\n";
                    }
                }
                // --------------------------------------

                int coachId = coachService->createCoach(name, capacity);
                if (!undoService->isActive())
                {
                    undoService->recordAction(ActionType::CREATE_COACH, coachId, -1, name,
                                              capacity);
                }
                loggerService->logAction("COACH_CREATE", "Coach: " + name);
                break;
            }
            case 2:
            {
                int coachId;
                std::cout << "Enter Coach ID to delete: ";
                std::cin >> coachId;
                coachService->deleteCoach(coachId);
                loggerService->logAction("COACH_DELETE", "Coach ID: " + std::to_string(coachId));
                break;
            }
            case 3:
            {
                int trainId, coachId, position;
                std::cout << "Enter Coach ID: ";
                std::cin >> coachId;
                std::cout << "Enter Train ID: ";
                std::cin >> trainId;
                std::cout << "Enter Position (-1 for end, 0 for front): ";
                std::cin >> position;
                coachService->linkCoach(coachId, trainId, position);
                loggerService->logAction("COACH_LINK", "Coach ID: " + std::to_string(coachId) +
                                                           " to Train: " + std::to_string(trainId));
                break;
            }
            case 4:
            {
                int trainId, coachId;
                std::cout << "Enter Coach ID: ";
                std::cin >> coachId;
                std::cout << "Enter Train ID to unlink from: ";
                std::cin >> trainId;
                coachService->unlinkCoach(coachId, trainId);
                loggerService->logAction("COACH_UNLINK",
                                         "Coach ID: " + std::to_string(coachId) +
                                             " from Train: " + std::to_string(trainId));
                break;
            }
            case 5:
            {
                int trainId;
                std::cout << "Enter Train ID to reverse: ";
                std::cin >> trainId;
                coachService->reverseTrain(trainId);
                loggerService->logAction("TRAIN_REVERSE", "Train: " + std::to_string(trainId));
                break;
            }
            case 6:
                coachService->listAllCoaches();
                break;
            case 7:
            {
                int trainId;
                std::cout << "Enter Train ID to traverse: ";
                std::cin >> trainId;
                coachService->traverseTrain(trainId);
                loggerService->logAction("TRAIN_TRAVERSE", "Train: " + std::to_string(trainId));
                break;
            }
            case 0:
                back = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

void TerminalUI::handleNetworkMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\n--- [Module 3] Railway Network ---\n";
        std::cout << "1. Add Station\n";
        std::cout << "2. Add Track (Link Stations)\n";
        std::cout << "3. Remove Station\n";
        std::cout << "4. Remove Track\n";
        std::cout << "5. Find Shortest Path\n";
        std::cout << "6. Show Network Map\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                std::string name;
                std::cout << "Enter Station Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                int stationId = networkService->createStation(name);
                if (!undoService->isActive())
                {
                    undoService->recordAction(ActionType::CREATE_STATION, stationId, -1, name);
                }
                loggerService->logAction("STATION_ADD", "Name: " + name);
                break;
            }
            case 2:
            {
                int startId, endId, distance;
                std::cout << "Enter Start Station ID: ";
                std::cin >> startId;
                std::cout << "Enter End Station ID: ";
                std::cin >> endId;
                std::cout << "Enter Distance (km): ";
                std::cin >> distance;
                networkService->linkStations(startId, endId, distance);
                if (!undoService->isActive())
                {
                    undoService->recordAction(ActionType::LINK_STATIONS, startId, endId, "",
                                              distance);
                }
                loggerService->logAction("TRACK_ADD", "From: " + std::to_string(startId) +
                                                          " To: " + std::to_string(endId));
                break;
            }
            case 3:
            {
                int id;
                std::cout << "Enter Station ID to remove: ";
                std::cin >> id;
                networkService->deleteStation(id);
                loggerService->logAction("STATION_REMOVE", "ID: " + std::to_string(id));
                break;
            }
            case 4:
            {
                int startId, endId;
                std::cout << "Enter Start Station ID: ";
                std::cin >> startId;
                std::cout << "Enter End Station ID: ";
                std::cin >> endId;
                networkService->unlinkStations(startId, endId);
                loggerService->logAction("TRACK_REMOVE", "From: " + std::to_string(startId) +
                                                             " To: " + std::to_string(endId));
                break;
            }
            case 5:
            {
                int startId, endId;
                std::cout << "Enter Start Station ID: ";
                std::cin >> startId;
                std::cout << "Enter End Station ID: ";
                std::cin >> endId;
                networkService->suggestRoute(startId, endId);
                loggerService->logAction("PATH_FIND", "From: " + std::to_string(startId) +
                                                          " To: " + std::to_string(endId));
                break;
            }
            case 6:
                networkService->showNetwork();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

void TerminalUI::handleSeatingMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\n--- [Module 4] Seating Chart ---\n";
        std::cout << "1. Book Seat\n";
        std::cout << "2. Cancel Booking\n";
        std::cout << "3. Check Seat Status\n";
        std::cout << "4. View Seating Chart\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                int trainId, seatNo;
                std::cout << "Enter Train ID: ";
                std::cin >> trainId;
                std::cout << "Enter Global Seat Number: ";
                std::cin >> seatNo;
                if (coachService->bookSeat(trainId, seatNo))
                {
                    loggerService->logAction("SEAT_BOOK", "Train: " + std::to_string(trainId) +
                                                              " Seat: " + std::to_string(seatNo));
                }
                break;
            }
            case 2:
            {
                int trainId, seatNo;
                std::cout << "Enter Train ID: ";
                std::cin >> trainId;
                std::cout << "Enter Global Seat Number: ";
                std::cin >> seatNo;
                if (coachService->cancelBooking(trainId, seatNo))
                {
                    loggerService->logAction("SEAT_CANCEL", "Train: " + std::to_string(trainId) +
                                                                " Seat: " + std::to_string(seatNo));
                }
                break;
            }
            case 3:
            {
                int trainId, seatNo;
                std::cout << "Enter Train ID: ";
                std::cin >> trainId;
                std::cout << "Enter Global Seat Number: ";
                std::cin >> seatNo;
                SeatStatus status = coachService->checkSeatStatus(trainId, seatNo);
                std::cout << "Seat Status: "
                          << (status == SeatStatus::Available ? "Available" : "Booked") << "\n";
                break;
            }
            case 4:
            {
                int trainId;
                std::cout << "Enter Train ID: ";
                std::cin >> trainId;
                coachService->viewSeatingChart(trainId);
                break;
            }
            case 0:
                back = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

void TerminalUI::handleSchedulingMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\n--- Scheduling (Operations) ---\n";
        std::cout << "1. Assign Route\n";
        std::cout << "2. Show Schedule\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                int trainId, startId, endId;
                std::cout << "Enter Train ID: ";
                std::cin >> trainId;
                std::cout << "Enter Start Station ID: ";
                std::cin >> startId;
                std::cout << "Enter Destination Station ID: ";
                std::cin >> endId;
                schedulingService->assignRoute(trainId, startId, endId);
                loggerService->logAction("SCHEDULE_ASSIGN",
                                         "Train: " + std::to_string(trainId) + " to Route: " +
                                             std::to_string(startId) + "-" + std::to_string(endId));
                break;
            }
            case 2:
                schedulingService->showSchedule();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

void TerminalUI::handleLogsMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\n--- [Module 5] System Logs ---\n";
        std::cout << "1. Show Recent Logs\n";
        std::cout << "2. Clear Logs\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                int count;
                std::cout << "How many logs to show? ";
                std::cin >> count;
                loggerService->showRecentLogs(count);
                break;
            }
            case 2:
                loggerService->clearLogs();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

void TerminalUI::handlePersistenceMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\n--- System Save/Load ---\n";
        std::cout << "1. Save System State\n";
        std::cout << "2. Load System State\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                coachService->saveData("coaches.txt");
                trainService->saveData("trains.txt");
                networkService->saveData("stations.txt");
                schedulingService->saveData("schedule.txt");
                loggerService->saveData("logs.txt");
                std::cout << "System state saved successfully.\n";

                break;
            }
            case 2:
            {
                coachService->loadData("coaches.txt");
                trainService->loadData("trains.txt", coachService->getCoachRegistry());
                networkService->loadData("stations.txt");
                schedulingService->loadData("schedule.txt");
                loggerService->loadData("logs.txt");
                std::cout << "System state loaded successfully.\n";

                break;
            }
            case 0:
                back = true;

                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

void TerminalUI::handleUndoRedoMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\n--- Undo / Redo ---\n";
        std::cout << "1. Undo Last Action\n";
        std::cout << "2. Redo Last Action\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        int choice = getChoice();
        switch (choice)
        {
            case 1:
                undoService->undo();
                break;
            case 2:
                undoService->redo();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}

#include "../TerminalUI.hpp"

#include <iostream>

#include "../../Services/UndoService.hpp"
#include "../ConsoleColors.hpp"  // <-- Include our new palette!

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
    std::cout << "\033[2J\033[H";

    std::cout << Color::BOLD << Color::BLUE << "\n====================================\n";
    std::cout << Color::CYAN << "      🚂 THE IRON NEXUS UI 🚂       \n";
    std::cout << Color::BLUE << "====================================\n" << Color::RESET;

    std::cout << "1. Train Registry (Module 1)\n";
    std::cout << "2. Coach Management (Module 2)\n";
    std::cout << "3. Railway Network (Module 3)\n";
    std::cout << "4. Seating Chart (Module 4)\n";
    std::cout << "5. Scheduling (Operations)\n";
    std::cout << "6. Operation Logs (Module 5)\n";
    std::cout << "7. System Save/Load\n";
    std::cout << "8. Undo/Redo\n";
    std::cout << Color::RED << "0. Exit\n" << Color::RESET;
    std::cout << Color::BLUE << "------------------------------------\n" << Color::RESET;

    std::cout << Color::YELLOW << "Choice: " << Color::RESET;

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
            std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
            clearScreen();
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
        std::cout << "\033[2J\033[H";
        std::cout << Color::BOLD << Color::CYAN << "\n--- [Module 1] Train Registry ---\n"
                  << Color::RESET;
        std::cout << "1. Register New Train\n";
        std::cout << "2. Decommission (Remove) Train\n";
        std::cout << "3. Find Train by ID\n";
        std::cout << "4. List All Trains (Fleet Patrol)\n";
        std::cout << "5. Emergency Stop Command\n";
        std::cout << Color::RED << "0. Back to Main Menu\n" << Color::RESET;
        std::cout << Color::YELLOW << "Choice: " << Color::RESET;

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                std::string name;
                std::cout << Color::CYAN << "Enter Train Name: " << Color::RESET;
                std::cin.ignore(10000, '\n');
                std::getline(std::cin, name);

                int id = trainService->registerTrain(name);
                if (!undoService->isActive())
                    undoService->recordAction(ActionType::REGISTER_TRAIN, id, -1, name);
                loggerService->logAction("TRAIN_REGISTER", "Name: " + name);

                clearScreen();
                break;
            }
            case 2:
            {
                int id;
                std::cout << Color::CYAN << "Enter Train ID to remove: " << Color::RESET;
                std::cin >> id;
                Train* t = trainService->findTrain(id);
                if (t)
                {
                    if (!undoService->isActive())
                        undoService->recordAction(ActionType::REMOVE_TRAIN, id, -1, t->getName());

                    // === INVARIANT FIX 4: Cascading Delete ===
                    schedulingService->decommissionRoute(id, true);
                    // =========================================

                    trainService->removeTrain(id);
                    loggerService->logAction("TRAIN_REMOVE", "ID: " + std::to_string(id));
                }
                else
                {
                    std::cout << Color::RED << "Train not found.\n" << Color::RESET;
                }
                clearScreen();
                break;
            }
            case 3:
            {
                int id;
                std::cout << Color::CYAN << "Enter Train ID to find: " << Color::RESET;
                std::cin >> id;
                Train* t = trainService->findTrain(id);
                if (t)
                    std::cout << Color::GREEN << "[Found] " << t->getName()
                              << " (ID: " << t->getId() << ")\n"
                              << Color::RESET;
                else
                    std::cout << Color::RED << "Train not found.\n" << Color::RESET;

                clearScreen();
                break;
            }
            case 4:
                trainService->listAllTrains();

                clearScreen();
                break;
            case 5:
            {
                int id;
                std::cout << Color::CYAN << "Enter Train ID for Emergency Stop: " << Color::RESET;
                std::cin >> id;
                trainService->emergencyStop(id);
                loggerService->logAction("EMERGENCY_STOP", "ID: " + std::to_string(id));

                clearScreen();
                break;
            }
            case 0:
                back = true;
                break;
            default:
                std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
                clearScreen();
        }
    }
}

void TerminalUI::handleCoachMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\033[2J\033[H";
        std::cout << Color::BOLD << Color::CYAN << "\n--- [Module 2] Coach Management ---\n"
                  << Color::RESET;
        std::cout << "1. Create Standalone Coach\n";
        std::cout << "2. Delete Coach\n";
        std::cout << "3. Link Coach to Train\n";
        std::cout << "4. Unlink Coach from Train\n";
        std::cout << "5. Reverse Train\n";
        std::cout << "6. List All Coaches\n";
        std::cout << "7. Traverse Train (View Linked Coaches)\n";
        std::cout << Color::RED << "0. Back\n" << Color::RESET;
        std::cout << Color::YELLOW << "Choice: " << Color::RESET;

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                int capacity = 0;
                std::string name;
                std::cout << Color::CYAN << "Enter Coach Name: " << Color::RESET;
                std::cin.ignore(10000, '\n');
                std::getline(std::cin, name);

                while (capacity <= 0)
                {
                    std::cout << Color::CYAN << "Enter Capacity (must be > 0): " << Color::RESET;
                    std::cin >> capacity;
                    if (capacity <= 0)
                        std::cout << Color::RED << "Invalid capacity! Please try again.\n"
                                  << Color::RESET;
                }

                int coachId = coachService->createCoach(name, capacity);
                if (!undoService->isActive())
                    undoService->recordAction(ActionType::CREATE_COACH, coachId, -1, name,
                                              capacity);
                loggerService->logAction("COACH_CREATE", "Coach: " + name);

                clearScreen();
                break;
            }
            case 2:
            {
                int coachId;
                std::cout << Color::CYAN << "Enter Coach ID to delete: " << Color::RESET;
                std::cin >> coachId;
                coachService->deleteCoach(coachId);
                loggerService->logAction("COACH_DELETE", "Coach ID: " + std::to_string(coachId));

                clearScreen();
                break;
            }
            case 3:
            {
                int trainId, coachId, position;
                std::cout << Color::CYAN << "Enter Coach ID: " << Color::RESET;
                std::cin >> coachId;
                std::cout << Color::CYAN << "Enter Train ID: " << Color::RESET;
                std::cin >> trainId;
                std::cout << Color::CYAN
                          << "Enter Position (-1 for end, 0 for front): " << Color::RESET;
                std::cin >> position;
                coachService->linkCoach(coachId, trainId, position);
                loggerService->logAction("COACH_LINK", "Coach ID: " + std::to_string(coachId) +
                                                           " to Train: " + std::to_string(trainId));

                clearScreen();
                break;
            }
            case 4:
            {
                int trainId, coachId;
                std::cout << Color::CYAN << "Enter Coach ID: " << Color::RESET;
                std::cin >> coachId;
                std::cout << Color::CYAN << "Enter Train ID to unlink from: " << Color::RESET;
                std::cin >> trainId;
                coachService->unlinkCoach(coachId, trainId);
                loggerService->logAction("COACH_UNLINK",
                                         "Coach ID: " + std::to_string(coachId) +
                                             " from Train: " + std::to_string(trainId));

                clearScreen();
                break;
            }
            case 5:
            {
                int trainId;
                std::cout << Color::CYAN << "Enter Train ID to reverse: " << Color::RESET;
                std::cin >> trainId;

                // === FIX: Record the action so we can undo it! ===
                if (!undoService->isActive())
                {
                    undoService->recordAction(ActionType::REVERSE_TRAIN, trainId);
                }
                // =================================================

                coachService->reverseTrain(trainId);
                loggerService->logAction("TRAIN_REVERSE", "Train: " + std::to_string(trainId));

                clearScreen();
                break;
            }
            case 6:
                coachService->listAllCoaches();

                clearScreen();
                break;
            case 7:
            {
                int trainId;
                std::cout << Color::CYAN << "Enter Train ID to traverse: " << Color::RESET;
                std::cin >> trainId;
                coachService->traverseTrain(trainId);
                loggerService->logAction("TRAIN_TRAVERSE", "Train: " + std::to_string(trainId));

                clearScreen();
                break;
            }
            case 0:
                back = true;
                break;
            default:
                std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
                clearScreen();
        }
    }
}

void TerminalUI::handleNetworkMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\033[2J\033[H";
        std::cout << Color::BOLD << Color::CYAN << "\n--- [Module 3] Railway Network ---\n"
                  << Color::RESET;
        std::cout << "1. Add Station\n";
        std::cout << "2. Add Track (Link Stations)\n";
        std::cout << "3. Remove Station\n";
        std::cout << "4. Remove Track\n";
        std::cout << "5. Find Shortest Path\n";
        std::cout << "6. Show Network Map\n";
        std::cout << Color::RED << "0. Back\n" << Color::RESET;
        std::cout << Color::YELLOW << "Choice: " << Color::RESET;

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                std::string name;
                std::cout << Color::CYAN << "Enter Station Name: " << Color::RESET;
                std::cin.ignore(10000, '\n');
                std::getline(std::cin, name);
                int stationId = networkService->createStation(name);
                if (!undoService->isActive())
                    undoService->recordAction(ActionType::CREATE_STATION, stationId, -1, name);
                loggerService->logAction("STATION_ADD", "Name: " + name);

                clearScreen();
                break;
            }
            case 2:
            {
                int startId, endId;
                int distance = 0;  // Initialize to 0 to trigger the loop

                std::cout << Color::CYAN << "Enter Start Station ID: " << Color::RESET;
                std::cin >> startId;
                std::cout << Color::CYAN << "Enter End Station ID: " << Color::RESET;
                std::cin >> endId;

                // === INVARIANT FIX 5: Validate Distance ===
                while (distance <= 0)
                {
                    std::cout << Color::CYAN
                              << "Enter Distance (km, must be > 0): " << Color::RESET;
                    std::cin >> distance;
                    if (distance <= 0)
                    {
                        std::cout << Color::RED
                                  << "Invalid distance! Please enter a positive number.\n"
                                  << Color::RESET;
                    }
                }
                // ==========================================

                networkService->linkStations(startId, endId, distance);
                if (!undoService->isActive())
                    undoService->recordAction(ActionType::LINK_STATIONS, startId, endId, "",
                                              distance);

                loggerService->logAction("TRACK_ADD", "From: " + std::to_string(startId) +
                                                          " To: " + std::to_string(endId));

                clearScreen();
                break;
            }
            case 3:
            {
                int id;
                std::cout << Color::CYAN << "Enter Station ID to remove: " << Color::RESET;
                std::cin >> id;

                // === INVARIANT FIX 4: Cascading Delete ===
                schedulingService->clearRoutesByStation(id);
                // =========================================

                networkService->deleteStation(id);
                loggerService->logAction("STATION_REMOVE", "ID: " + std::to_string(id));

                clearScreen();
                break;
            }
            case 4:
            {
                int startId, endId;
                std::cout << Color::CYAN << "Enter Start Station ID: " << Color::RESET;
                std::cin >> startId;
                std::cout << Color::CYAN << "Enter End Station ID: " << Color::RESET;
                std::cin >> endId;
                networkService->unlinkStations(startId, endId);
                loggerService->logAction("TRACK_REMOVE", "From: " + std::to_string(startId) +
                                                             " To: " + std::to_string(endId));

                clearScreen();
                break;
            }
            case 5:
            {
                int startId, endId;
                std::cout << Color::CYAN << "Enter Start Station ID: " << Color::RESET;
                std::cin >> startId;
                std::cout << Color::CYAN << "Enter End Station ID: " << Color::RESET;
                std::cin >> endId;
                networkService->suggestRoute(startId, endId);
                loggerService->logAction("PATH_FIND", "From: " + std::to_string(startId) +
                                                          " To: " + std::to_string(endId));

                clearScreen();
                break;
            }
            case 6:
                networkService->showNetwork();

                clearScreen();
                break;
            case 0:
                back = true;
                break;
            default:
                std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
                clearScreen();
        }
    }
}

void TerminalUI::handleSeatingMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\033[2J\033[H";
        std::cout << Color::BOLD << Color::CYAN << "\n--- [Module 4] Seating Chart ---\n"
                  << Color::RESET;
        std::cout << "1. Book Seat\n";
        std::cout << "2. Cancel Booking\n";
        std::cout << "3. Check Seat Status\n";
        std::cout << "4. View Seating Chart\n";
        std::cout << Color::RED << "0. Back\n" << Color::RESET;
        std::cout << Color::YELLOW << "Choice: " << Color::RESET;

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                int trainId, seatNo;
                std::cout << Color::CYAN << "Enter Train ID: " << Color::RESET;
                std::cin >> trainId;
                std::cout << Color::CYAN << "Enter Global Seat Number: " << Color::RESET;
                std::cin >> seatNo;
                if (coachService->bookSeat(trainId, seatNo))
                {
                    loggerService->logAction("SEAT_BOOK", "Train: " + std::to_string(trainId) +
                                                              " Seat: " + std::to_string(seatNo));

                    clearScreen();
                }
                break;
            }
            case 2:
            {
                int trainId, seatNo;
                std::cout << Color::CYAN << "Enter Train ID: " << Color::RESET;
                std::cin >> trainId;
                std::cout << Color::CYAN << "Enter Global Seat Number: " << Color::RESET;
                std::cin >> seatNo;
                if (coachService->cancelBooking(trainId, seatNo))
                {
                    loggerService->logAction("SEAT_CANCEL", "Train: " + std::to_string(trainId) +
                                                                " Seat: " + std::to_string(seatNo));
                }

                clearScreen();
                break;
            }
            case 3:
            {
                int trainId, seatNo;
                std::cout << Color::CYAN << "Enter Train ID: " << Color::RESET;
                std::cin >> trainId;
                std::cout << Color::CYAN << "Enter Global Seat Number: " << Color::RESET;
                std::cin >> seatNo;
                SeatStatus status = coachService->checkSeatStatus(trainId, seatNo);
                std::cout << "Seat Status: "
                          << (status == SeatStatus::Available ? Color::GREEN + "Available"
                                                              : Color::RED + "Booked")
                          << Color::RESET << "\n";

                clearScreen();
                break;
            }
            case 4:
            {
                int trainId;
                std::cout << Color::CYAN << "Enter Train ID: " << Color::RESET;
                std::cin >> trainId;
                coachService->viewSeatingChart(trainId);

                clearScreen();
                break;
            }
            case 0:
                back = true;

                break;
            default:
                std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
                clearScreen();
        }
    }
}

void TerminalUI::handleSchedulingMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\033[2J\033[H";
        std::cout << Color::BOLD << Color::CYAN << "\n--- Scheduling (Operations) ---\n"
                  << Color::RESET;
        std::cout << "1. Assign Route\n";
        std::cout << "2. Show Schedule\n";
        std::cout << Color::RED << "0. Back\n" << Color::RESET;
        std::cout << Color::YELLOW << "Choice: " << Color::RESET;

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                int trainId, startId, endId;
                std::cout << Color::CYAN << "Enter Train ID: " << Color::RESET;
                std::cin >> trainId;
                std::cout << Color::CYAN << "Enter Start Station ID: " << Color::RESET;
                std::cin >> startId;
                std::cout << Color::CYAN << "Enter Destination Station ID: " << Color::RESET;
                std::cin >> endId;
                schedulingService->assignRoute(trainId, startId, endId);
                loggerService->logAction("SCHEDULE_ASSIGN",
                                         "Train: " + std::to_string(trainId) + " to Route: " +
                                             std::to_string(startId) + "-" + std::to_string(endId));

                clearScreen();
                break;
            }
            case 2:
                schedulingService->showSchedule();

                clearScreen();
                break;
            case 0:
                back = true;

                break;
            default:
                std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
                clearScreen();
        }
    }
}

void TerminalUI::handleLogsMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\033[2J\033[H";
        std::cout << Color::BOLD << Color::CYAN << "\n--- [Module 5] System Logs ---\n"
                  << Color::RESET;
        std::cout << "1. Show Recent Logs\n";
        std::cout << "2. Clear Logs\n";
        std::cout << Color::RED << "0. Back\n" << Color::RESET;
        std::cout << Color::YELLOW << "Choice: " << Color::RESET;

        int choice = getChoice();
        switch (choice)
        {
            case 1:
            {
                int count;
                std::cout << Color::CYAN << "How many logs to show? " << Color::RESET;
                std::cin >> count;
                loggerService->showRecentLogs(count);

                clearScreen();
                break;
            }
            case 2:
                loggerService->clearLogs();

                clearScreen();
                break;
            case 0:
                back = true;

                break;
            default:
                std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
                clearScreen();
        }
    }
}

void TerminalUI::handlePersistenceMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\033[2J\033[H";
        std::cout << Color::BOLD << Color::CYAN << "\n--- System Save/Load ---\n" << Color::RESET;
        std::cout << "1. Save System State\n";
        std::cout << "2. Load System State\n";
        std::cout << Color::RED << "0. Back\n" << Color::RESET;
        std::cout << Color::YELLOW << "Choice: " << Color::RESET;

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

                coachService->exportStructuralData("coaches_structural.txt");
                trainService->exportStructuralData("trains_structural.txt");

                std::cout << Color::GREEN << "System state saved successfully.\n" << Color::RESET;
                std::cout << Color::GREEN
                          << "Structural tree diagrams exported to *_structural.txt\n"
                          << Color::RESET;

                clearScreen();
                break;
            }
            case 2:
            {
                coachService->loadData("coaches.txt");
                trainService->loadData("trains.txt", coachService->getCoachRegistry());
                networkService->loadData("stations.txt");
                schedulingService->loadData("schedule.txt");
                loggerService->loadData("logs.txt");
                std::cout << Color::GREEN << "System state loaded successfully.\n" << Color::RESET;

                clearScreen();
                break;
            }
            case 0:
                back = true;

                break;
            default:
                std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
                clearScreen();
        }
    }
}

void TerminalUI::handleUndoRedoMenu()
{
    bool back = false;
    while (!back)
    {
        std::cout << "\033[2J\033[H";
        std::cout << Color::BOLD << Color::CYAN << "\n--- Undo / Redo ---\n" << Color::RESET;
        std::cout << "1. Undo Last Action\n";
        std::cout << "2. Redo Last Action\n";
        std::cout << Color::RED << "0. Back\n" << Color::RESET;
        std::cout << Color::YELLOW << "Choice: " << Color::RESET;

        int choice = getChoice();
        switch (choice)
        {
            case 1:
                undoService->undo();
                clearScreen();
                break;
            case 2:
                undoService->redo();
                clearScreen();
                break;
            case 0:
                back = true;

                break;
            default:
                std::cout << Color::RED << "Invalid choice!\n" << Color::RESET;
                clearScreen();
        }
    }
}

void TerminalUI::clearScreen()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.clear();
    // Peek to check if there's already a newline in the buffer to avoid double-pausing
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::cin.get();

    // Clear the screen and move cursor to top
    std::cout << "\033[2J\033[H";
}
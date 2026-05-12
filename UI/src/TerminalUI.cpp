#include "../TerminalUI.hpp"

#include <iostream>

TerminalUI::TerminalUI(TrainService* ts, CoachService* cs, NetworkService* ns,
                       SchedulingService* ss, LoggerService* ls)
    : trainService(ts),
      coachService(cs),
      networkService(ns),
      schedulingService(ss),
      loggerService(ls),
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
                trainService->registerTrain(name);
                loggerService->logAction("TRAIN_REGISTER", "Name: " + name);
                break;
            }
            case 2:
            {
                int id;
                std::cout << "Enter Train ID to remove: ";
                std::cin >> id;
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
    std::cout << "\n--- Coach Management ---\n";
    std::cout << "1. Add Coach\n2. Remove Coach\n3. Reverse Train\n0. Back\n";
}

void TerminalUI::handleNetworkMenu()
{
    std::cout << "\n--- Railway Network ---\n";
    std::cout << "1. Add Station\n2. Add Track\n3. Find Shortest Path\n0. Back\n";
}

void TerminalUI::handleSeatingMenu()
{
    std::cout << "\n--- Seating Chart ---\n";
    std::cout << "1. Book Seat\n2. Cancel Booking\n3. View Chart\n0. Back\n";
}

void TerminalUI::handleSchedulingMenu()
{
    std::cout << "\n--- Scheduling ---\n";
    std::cout << "1. Assign Route\n2. Show Schedule\n0. Back\n";
}

void TerminalUI::handleLogsMenu()
{
    std::cout << "\n--- System Logs ---\n";
}

void TerminalUI::handlePersistenceMenu()
{
    std::cout << "\n--- Save/Load System ---\n";
}

#include "../TerminalUI.hpp"
#include <iostream>

TerminalUI::TerminalUI(TrainService* ts, CoachService* cs, NetworkService* ns, SchedulingService* ss)
    : trainService(ts), coachService(cs), networkService(ns), schedulingService(ss), running(false)
{
}

TerminalUI::~TerminalUI() {}

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
    case 1: handleTrainMenu(); break;
    case 2: handleCoachMenu(); break;
    case 3: handleNetworkMenu(); break;
    case 4: handleSeatingMenu(); break;
    case 5: handleSchedulingMenu(); break;
    case 6: handleLogsMenu(); break;
    case 7: handlePersistenceMenu(); break;
    case 0: running = false; break;
    default: std::cout << "Invalid choice!\n";
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

// Module Menu Skeletons
void TerminalUI::handleTrainMenu()
{
    std::cout << "\n--- Train Registry ---\n";
    std::cout << "1. Register Train\n2. Remove Train\n3. List Fleet\n0. Back\n";
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

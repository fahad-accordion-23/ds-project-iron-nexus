#ifndef TERMINAL_UI_HPP
#define TERMINAL_UI_HPP

#include "../Services/TrainService.hpp"
#include "../Services/CoachService.hpp"
#include "../Services/NetworkService.hpp"
#include "../Services/SchedulingService.hpp"
#include "../Services/LoggerService.hpp"

/**
 * @brief Menu-driven Terminal User Interface for The Iron Nexus.
 */
class TerminalUI
{
private:
    TrainService* trainService;
    CoachService* coachService;
    NetworkService* networkService;
    SchedulingService* schedulingService;
    LoggerService* loggerService;

    bool running;

    // Menu handlers
    void showMainMenu();
    void handleTrainMenu();
    void handleCoachMenu();
    void handleNetworkMenu();
    void handleSeatingMenu();
    void handleSchedulingMenu();
    void handleLogsMenu();
    void handlePersistenceMenu();

    // Helper for input
    int getChoice();

public:
    TerminalUI(TrainService* ts, CoachService* cs, NetworkService* ns, SchedulingService* ss, LoggerService* ls);
    ~TerminalUI();

    /**
     * @brief Starts the UI loop.
     */
    void start();
};

#endif // TERMINAL_UI_HPP

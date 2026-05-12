#ifndef TERMINAL_UI_HPP
#define TERMINAL_UI_HPP

#include "../Services/CoachService.hpp"
#include "../Services/LoggerService.hpp"
#include "../Services/NetworkService.hpp"
#include "../Services/SchedulingService.hpp"
#include "../Services/TrainService.hpp"

class UndoService;

class TerminalUI
{
private:
    TrainService* trainService;
    CoachService* coachService;
    NetworkService* networkService;
    SchedulingService* schedulingService;
    LoggerService* loggerService;
    UndoService* undoService;

    bool running;

    void showMainMenu();
    void handleTrainMenu();
    void handleCoachMenu();
    void handleNetworkMenu();
    void handleSeatingMenu();
    void handleSchedulingMenu();
    void handleLogsMenu();
    void handlePersistenceMenu();
    void handleUndoRedoMenu();

    int getChoice();

public:
    TerminalUI(TrainService* ts, CoachService* cs, NetworkService* ns, SchedulingService* ss,
               LoggerService* ls, UndoService* us);
    ~TerminalUI();

    void start();
};

#endif

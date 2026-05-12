#include "Services/CoachService.hpp"
#include "Services/LoggerService.hpp"
#include "Services/NetworkService.hpp"
#include "Services/SchedulingService.hpp"
#include "Services/TrainService.hpp"
#include "Services/UndoService.hpp"
#include "UI/TerminalUI.hpp"

int main()
{
    TrainService trainService;
    CoachService coachService(&trainService);
    NetworkService networkService;
    SchedulingService schedulingService;
    LoggerService loggerService;
    UndoService undoService(&trainService, &coachService, &networkService, &schedulingService);

    TerminalUI ui(&trainService, &coachService, &networkService, &schedulingService, &loggerService,
                  &undoService);
    ui.start();

    return 0;
}

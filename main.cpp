#include "Services/TrainService.hpp"
#include "Services/CoachService.hpp"
#include "Services/NetworkService.hpp"
#include "Services/SchedulingService.hpp"
#include "UI/TerminalUI.hpp"

int main()
{
    // Initialize Services
    TrainService trainService;
    CoachService coachService;
    NetworkService networkService;
    SchedulingService schedulingService;

    // Initialize and Start UI
    TerminalUI ui(&trainService, &coachService, &networkService, &schedulingService);
    ui.start();

    return 0;
}

#include "../SchedulingService.hpp"

#include <iostream>

#include "../../Repositories/ScheduleRepository.hpp"
#include "../../Structures/Stack.hpp"
#include "../../UI/ConsoleColors.hpp"

SchedulingService::SchedulingService(TrainService* ts, NetworkService* ns)
{
    schedule = new HashTable<Train::TrainID, Station::StationID>();

    this->trainService = ts;
    this->networkService = ns;
}

SchedulingService::~SchedulingService()
{
    delete schedule;
}

void SchedulingService::assignRoute(Train::TrainID trainId, Station::StationID startId,
                                    Station::StationID endId)
{
    // 1. Validate Train
    if (trainService->findTrain(trainId) == nullptr)
    {
        std::cout << "[SchedulingService] Error: Train " << trainId << " does not exist.\n";
        return;
    }

    // 2. Validate Stations
    if (networkService->findStation(startId) == nullptr)
    {
        std::cout << "[SchedulingService] Error: Start Station " << startId << " does not exist.\n";
        return;
    }
    if (networkService->findStation(endId) == nullptr)
    {
        std::cout << "[SchedulingService] Error: Destination Station " << endId
                  << " does not exist.\n";
        return;
    }

    // 3. Optional: Map Start -> End to verify a path exists (Network bounds check)
    if (startId == endId)
    {
        std::cout << "[SchedulingService] Error: Start and End stations cannot be the same.\n";
        return;
    }

    // === INVARIANT FIX 6: Prevent Silent Overwrites ===
    try
    {
        schedule->search(trainId);
        // If search succeeds, it means a route already exists!
        std::cout << Color::RED << "[SchedulingService] Error: Train " << trainId
                  << " is already scheduled. Please decommission its current route first.\n"
                  << Color::RESET;
        return;
    }
    catch (...)
    {
        // Expected behavior: Train is not scheduled. Proceed.
    }
    // ==================================================

    // 4. Assign the route
    schedule->insert(trainId, endId);
    std::cout << Color::GREEN << "[SchedulingService] Train " << trainId
              << " successfully assigned route: Station " << startId << " -> Station " << endId
              << "\n"
              << Color::RESET;

    // As per your sequence diagram, optionally trigger the route suggestion
    networkService->suggestRoute(startId, endId);
}

void SchedulingService::decommissionRoute(Train::TrainID trainId, bool silent)
{
    try
    {
        schedule->search(trainId);
        schedule->remove(trainId);

        if (!silent)
        {
            std::cout << Color::GREEN << "[SchedulingService] Train " << trainId
                      << " route cleared.\n";
            std::cout << Color::RESET;
        }
        else
        {
            std::cout << Color::YELLOW << "[SchedulingService] Train " << trainId
                      << " route cleared (Silent).\n";
            std::cout << Color::RESET;
        }
    }
    catch (...)
    {
        if (!silent)
        {
            std::cout << Color::RED << "[SchedulingService] Error: No assignment for Train "
                      << trainId << ".\n";
            std::cout << Color::RESET;
        }
    }
}

Station::StationID SchedulingService::getDestination(Train::TrainID trainId) const
{
    try
    {
        return schedule->search(trainId);
    }
    catch (...)
    {
        return -1;
    }
}

void SchedulingService::showSchedule() const
{
    std::cout << "\n========== ACTIVE SCHEDULE ==========\n";
    int count = 0;
    schedule->forEach(
        [&count](Train::TrainID trainId, Station::StationID stationId)
        {
            std::cout << "  Train " << trainId << " -> Station " << stationId << "\n";
            count++;
        });
    if (count == 0)
    {
        std::cout << "  (No active routes)\n";
    }
    std::cout << "=====================================\n";
}

void SchedulingService::saveData(const std::string& filename) const
{
    ScheduleRepository::saveToFile(filename, schedule);
}

void SchedulingService::loadData(const std::string& filename)
{
    ScheduleRepository::loadFromFile(filename, schedule);
}

void SchedulingService::clearRoutesByStation(Station::StationID stationId)
{
    // We cannot modify a HashTable while iterating it, so we use a Stack to hold IDs to remove
    Stack<Train::TrainID> toRemove;

    schedule->forEach(
        [&toRemove, stationId](Train::TrainID tId, Station::StationID sId)
        {
            if (sId == stationId)
            {
                toRemove.push(tId);
            }
        });

    while (!toRemove.isEmpty())
    {
        Train::TrainID tId = toRemove.pop();
        schedule->remove(tId);
        std::cout << Color::YELLOW << "[SchedulingService] Auto-cleared route for Train " << tId
                  << " due to station closure.\n"
                  << Color::RESET;
    }
}
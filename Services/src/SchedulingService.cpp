#include "../SchedulingService.hpp"

#include <iostream>

#include "../../Repositories/ScheduleRepository.hpp"

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

    // 4. Assign the route
    schedule->insert(trainId, endId);
    std::cout << "[SchedulingService] Train " << trainId << " successfully assigned route: Station "
              << startId << " -> Station " << endId << "\n";

    // As per your sequence diagram, optionally trigger the route suggestion
    networkService->suggestRoute(startId, endId);
}

void SchedulingService::decommissionRoute(Train::TrainID trainId)
{
    try
    {
        schedule->search(trainId);
        schedule->remove(trainId);
        std::cout << "[SchedulingService] Train " << trainId << " route cleared.\n";
    }
    catch (...)
    {
        std::cout << "[SchedulingService] Error: No assignment for Train " << trainId << ".\n";
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

#include "../SchedulingService.hpp"

#include <iostream>

SchedulingService::SchedulingService()
{
    schedule = new HashTable<Train::TrainID, Station::StationID>();
}

SchedulingService::~SchedulingService()
{
    delete schedule;
}

void SchedulingService::assignRoute(Train::TrainID trainId, Station::StationID startId,
                                    Station::StationID endId)
{
    schedule->insert(trainId, endId);
    std::cout << "[SchedulingService] Train " << trainId << " assigned route: Station " << startId
              << " -> Station " << endId << "\n";
}

void SchedulingService::decommissionRoute(Train::TrainID trainId)
{
    try
    {
        schedule->search(trainId);  // Check if exists
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
    schedule->forEach([&count](Train::TrainID trainId, Station::StationID stationId) {
        std::cout << "  Train " << trainId << " -> Station " << stationId << "\n";
        count++;
    });
    if (count == 0) {
        std::cout << "  (No active routes)\n";
    }
    std::cout << "=====================================\n";
}

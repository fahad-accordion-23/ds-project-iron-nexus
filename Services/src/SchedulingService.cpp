#include "../SchedulingService.hpp"

SchedulingService::SchedulingService() : schedule(nullptr)
{
    // schedule = new HashTable<Train::TrainID, Station::StationID>();
}

SchedulingService::~SchedulingService()
{
    // delete schedule;
}

void SchedulingService::assignRoute(Train::TrainID trainId, Station::StationID startId, Station::StationID endId)
{
    // 1. Verify trainId via TrainService
    // 2. Calculate optimal route via NetworkService
    // 3. Update schedule: schedule->insert(trainId, endId);
}

void SchedulingService::decommissionRoute(Train::TrainID trainId)
{
    // schedule->remove(trainId);
}

Station::StationID SchedulingService::getDestination(Train::TrainID trainId) const
{
    // return schedule->search(trainId);
    return -1;
}

void SchedulingService::showSchedule() const
{
    // Traverse schedule and display assignments
}

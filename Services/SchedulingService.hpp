#ifndef SCHEDULING_SERVICE_HPP
#define SCHEDULING_SERVICE_HPP

#include "../Railway/Station.hpp"
#include "../Structures/HashTable.hpp"
#include "../Train/Train.hpp"
#include "./NetworkService.hpp"
#include "./TrainService.hpp"

class SchedulingService
{
private:
    HashTable<Train::TrainID, Station::StationID>* schedule;

    TrainService* trainService;
    NetworkService* networkService;

public:
    SchedulingService(TrainService* ts, NetworkService* ns);
    ~SchedulingService();

    void assignRoute(Train::TrainID trainId, Station::StationID startId, Station::StationID endId);

    void decommissionRoute(Train::TrainID trainId);

    Station::StationID getDestination(Train::TrainID trainId) const;

    void showSchedule() const;

    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);

    void clearRoutesByStation(Station::StationID stationId);
};

#endif

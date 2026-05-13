#ifndef RAILWAY_NETWORK_HPP
#define RAILWAY_NETWORK_HPP

#include "../Structures/Graph.hpp"
#include "Station.hpp"

class RailwayNetwork
{
private:
    Graph<Station*>* network;
    CircularDoublyLinkedList<Station*>* stationList;
    static const int MAX_HUBS = 15;

    Station* findStationById(Station::StationID id) const;

public:
    RailwayNetwork();
    ~RailwayNetwork();

    void addStation(Station* station);

    void removeStation(Station::StationID id);

    void connectStations(Station::StationID startId, Station::StationID endId, int distance);

    void disconnectStations(Station::StationID startId, Station::StationID endId);

    void findOptimalRoute(Station::StationID startId, Station::StationID endId);

    void displayMap() const;

    template <typename Func>
    void forEachTrack(Func callback) const;
};

template <typename Func>
void RailwayNetwork::forEachTrack(Func callback) const
{
    if (network) network->forEachEdge(callback);
}

#endif

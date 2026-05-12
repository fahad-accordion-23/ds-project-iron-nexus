#include "../RailwayNetwork.hpp"

RailwayNetwork::RailwayNetwork() : network(nullptr)
{
    // network = new Graph<Station*>(); // Initialize once implemented
}

RailwayNetwork::~RailwayNetwork()
{
    // delete network;
}

void RailwayNetwork::addStation(Station* station)
{
    // Logic: network->addStation(station);
}

void RailwayNetwork::removeStation(Station::StationID id)
{
    // Logic: find station and network->removeStation(station);
}

void RailwayNetwork::connectStations(Station::StationID startId, Station::StationID endId, int distance, int travelTime)
{
    // Logic: network->addTrack(startId, endId, distance or travelTime);
}

void RailwayNetwork::disconnectStations(Station::StationID startId, Station::StationID endId)
{
    // Logic: network->removeTrack(startId, endId);
}

void RailwayNetwork::findOptimalRoute(Station::StationID startId, Station::StationID endId, bool useTravelTime)
{
    // Logic: network->dijkstra(startId, endId);
}

void RailwayNetwork::displayMap() const
{
    // Logic: network->display();
}

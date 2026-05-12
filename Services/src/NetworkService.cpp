#include "../NetworkService.hpp"

NetworkService::NetworkService() : network(nullptr), stationRegistry(nullptr)
{
    // network = new RailwayNetwork();
    // stationRegistry = new AVLTree<Station::StationID, Station*>();
}

NetworkService::~NetworkService()
{
    // delete network;
    // delete stationRegistry;
}

void NetworkService::createStation(const std::string& name)
{
    // Station* station = Station::Register(name);
    // stationRegistry->insert(station->getId(), station);
    // network->addStation(station);
}

void NetworkService::deleteStation(Station::StationID id)
{
    // Station* station = stationRegistry->search(id);
    // if (station) {
    //     network->removeStation(id);
    //     stationRegistry->remove(id);
    //     delete station;
    // }
}

void NetworkService::linkStations(Station::StationID startId, Station::StationID endId, int distance, int time)
{
    // network->connectStations(startId, endId, distance, time);
}

void NetworkService::unlinkStations(Station::StationID startId, Station::StationID endId)
{
    // network->disconnectStations(startId, endId);
}

void NetworkService::suggestRoute(Station::StationID startId, Station::StationID endId, bool fastTrack)
{
    // network->findOptimalRoute(startId, endId, fastTrack);
}

void NetworkService::showNetwork() const
{
    // network->displayMap();
}

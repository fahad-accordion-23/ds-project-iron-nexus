#include "../NetworkService.hpp"

#include <iostream>

#include "../../Repositories/StationRepository.hpp"

NetworkService::NetworkService()
{
    network = new RailwayNetwork();
    stationRegistry = new AVLTree<Station::StationID, Station*>();
}

NetworkService::~NetworkService()
{
    stationRegistry->traverseInOrder([](Station::StationID, Station* station) { delete station; });
    delete stationRegistry;
    delete network;
}

void NetworkService::createStation(const std::string& name)
{
    Station* station = Station::Register(name);
    stationRegistry->insert(station->getId(), station);
    network->addStation(station);
    std::cout << "[NetworkService] Station '" << name << "' created with ID: " << station->getId()
              << "\n";
}

void NetworkService::deleteStation(Station::StationID id)
{
    try
    {
        Station* station = stationRegistry->search(id);
        network->removeStation(id);
        stationRegistry->remove(id);
        std::cout << "[NetworkService] Station '" << station->getName() << "' (ID: " << id
                  << ") deleted.\n";
        delete station;
    }
    catch (...)
    {
        std::cout << "[NetworkService] Error: Station ID " << id << " not found.\n";
    }
}

void NetworkService::linkStations(Station::StationID startId, Station::StationID endId,
                                  int distance, int time)
{
    network->connectStations(startId, endId, distance, time);
    std::cout << "[NetworkService] Track established between stations " << startId << " and "
              << endId << " (Distance: " << distance << "km, Time: " << time << "min)\n";
}

void NetworkService::unlinkStations(Station::StationID startId, Station::StationID endId)
{
    network->disconnectStations(startId, endId);
    std::cout << "[NetworkService] Track removed between stations " << startId << " and " << endId
              << "\n";
}

void NetworkService::suggestRoute(Station::StationID startId, Station::StationID endId,
                                  bool fastTrack)
{
    std::cout << "\n========== ROUTE SUGGESTION ==========\n";
    std::cout << "  Mode: " << (fastTrack ? "Fastest Time" : "Shortest Distance") << "\n";
    network->findOptimalRoute(startId, endId, fastTrack);
    std::cout << "=======================================\n";
}

void NetworkService::saveData(const std::string& filename) const
{
    StationRepository::saveToFile(filename, stationRegistry);
}

void NetworkService::loadData(const std::string& filename)
{
    StationRepository::loadFromFile(filename, stationRegistry);
}

void NetworkService::showNetwork() const
{
    std::cout << "\n========== RAILWAY NETWORK MAP ==========\n";
    network->displayMap();
    std::cout << "==========================================\n";
}

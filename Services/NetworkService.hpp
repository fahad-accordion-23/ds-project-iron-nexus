#ifndef NETWORK_SERVICE_HPP
#define NETWORK_SERVICE_HPP

#include <string>

#include "../Railway/RailwayNetwork.hpp"
#include "../Railway/Station.hpp"
#include "../Structures/AVLTree.hpp"

class NetworkService
{
private:
    RailwayNetwork* network;
    AVLTree<Station::StationID, Station*>* stationRegistry;

public:
    NetworkService();
    ~NetworkService();

    Station::StationID createStation(const std::string& name);

    void rehydrateStation(Station::StationID id, const std::string& name);

    void deleteStation(Station::StationID id);

    void linkStations(Station::StationID startId, Station::StationID endId, int distance, int time);

    void unlinkStations(Station::StationID startId, Station::StationID endId);

    void getShortestPath(Station::StationID startId, Station::StationID endId,
                         bool optimizeForTime);

    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);

    void suggestRoute(Station::StationID startId, Station::StationID endId, bool fastTrack = false);

    void showNetwork() const;
};

#endif

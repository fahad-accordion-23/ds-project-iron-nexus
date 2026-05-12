#ifndef NETWORK_SERVICE_HPP
#define NETWORK_SERVICE_HPP

#include <string>

#include "../Railway/RailwayNetwork.hpp"
#include "../Railway/Station.hpp"
#include "../Structures/AVLTree.hpp"

/**
 * @brief Application service for managing the Railway Network (Module 3).
 */
class NetworkService
{
private:
    RailwayNetwork* network;
    AVLTree<Station::StationID, Station*>* stationRegistry;  // For O(log N) station lookups

public:
    NetworkService();
    ~NetworkService();

    /**
     * @brief Create and add a new station to the network.
     */
    void createStation(const std::string& name);

    /**
     * @brief Remove a station and all its connections.
     */
    void deleteStation(Station::StationID id);

    /**
     * @brief Link two stations with a track.
     */
    void linkStations(Station::StationID startId, Station::StationID endId, int distance, int time);

    /**
     * @brief Unlink two stations.
     */
    void unlinkStations(Station::StationID startId, Station::StationID endId);

    /**
     * @brief Find and display the shortest path using Dijkstra's algorithm.
     */
    void getShortestPath(Station::StationID startId, Station::StationID endId,
                         bool optimizeForTime);

    /**
     * @brief Persistence delegation
     */
    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);

    /**
     * @brief Suggest the best route between two stations.
     */
    void suggestRoute(Station::StationID startId, Station::StationID endId, bool fastTrack = false);

    /**
     * @brief Show the entire railway map.
     */
    void showNetwork() const;
};

#endif  // NETWORK_SERVICE_HPP

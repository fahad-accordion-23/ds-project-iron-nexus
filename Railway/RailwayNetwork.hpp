#ifndef RAILWAY_NETWORK_HPP
#define RAILWAY_NETWORK_HPP

#include <string>
#include "../Structures/Graph.hpp"
#include "Station.hpp"

/**
 * @brief Manages the railway topology (stations and tracks).
 */
class RailwayNetwork
{
private:
    Graph<Station*>* network;
    static const int MAX_HUBS = 15;

public:
    RailwayNetwork();
    ~RailwayNetwork();

    /**
     * @brief Add a station to the network.
     */
    void addStation(Station* station);

    /**
     * @brief Remove a station from the network.
     */
    void removeStation(Station::StationID id);

    /**
     * @brief Connect two stations with a track.
     * @param distance Distance in kilometers.
     * @param travelTime Time in minutes.
     */
    void connectStations(Station::StationID startId, Station::StationID endId, int distance, int travelTime);

    /**
     * @brief Disconnect two stations.
     */
    void disconnectStations(Station::StationID startId, Station::StationID endId);

    /**
     * @brief Find the most efficient path between two stations.
     * @param useTravelTime If true, optimizes for time; otherwise for distance.
     */
    void findOptimalRoute(Station::StationID startId, Station::StationID endId, bool useTravelTime = false);

    /**
     * @brief Display the network map.
     */
    void displayMap() const;
};

#endif // RAILWAY_NETWORK_HPP

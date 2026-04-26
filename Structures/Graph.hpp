#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "CircularDoublyLinkedList.hpp"

/**
 * @brief Adjacency list based Graph for the railway network.
 * @tparam T The type of vertex data (e.g., Station name).
 */
template<typename T>
class Graph
{
private:
    struct Edge
    {
        int destinationIndex;
        int weight; // Distance/time between stations
    };

    struct Vertex
    {
        T data;
        CircularDoublyLinkedList<Edge> adjacencyList;
    };

    CircularDoublyLinkedList<Vertex> vertices;

public:
    Graph();
    ~Graph();

    /**
     * @brief Add a new station (vertex) to the network.
     */
    void addStation(const T& station);

    /**
     * @brief Connect two stations with a track (bi-directional edge).
     */
    void addTrack(const T& start, const T& end, int distance);

    /**
     * @brief Find the shortest path between two stations (Dijkstra's Algorithm).
     */
    void findShortestRoute(const T& start, const T& end);

    /**
     * @brief Display the entire network.
     */
    void displayNetwork() const;
};

#endif // GRAPH_HPP

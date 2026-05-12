#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "CircularDoublyLinkedList.hpp"

/**
 * @brief Adjacency list based Graph for the railway network.
 * @tparam T The type of vertex data (e.g., Station name).
 */
template <typename T>
class Graph
{
private:
    struct Edge
    {
        int destinationIndex;
        int weight;  // Distance/time between stations
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
     * @brief Add a new node (vertex) to the graph.
     */
    void addNode(const T& data);

    /**
     * @brief Connect two nodes with an edge.
     */
    void addEdge(const T& start, const T& end, int weight);

    /**
     * @brief Remove a node (vertex) and all incident edges.
     */
    void removeNode(const T& data);

    /**
     * @brief Remove an edge between two nodes.
     */
    void removeEdge(const T& start, const T& end);

    /**
     * @brief Find the shortest path between two nodes (Dijkstra's Algorithm).
     */
    void findShortestPath(const T& start, const T& end);

    /**
     * @brief Display the entire graph.
     */
    void displayGraph() const;
};

#endif  // GRAPH_HPP

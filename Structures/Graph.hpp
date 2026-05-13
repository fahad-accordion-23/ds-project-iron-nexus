#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <climits>
#include <iostream>
#include <stdexcept>

#include "CircularDoublyLinkedList.hpp"

template <typename T>
class Graph
{
private:
    struct Edge
    {
        int destinationIndex;
        int weight;
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

    void addNode(const T& data);

    void addEdge(const T& start, const T& end, int weight);

    void removeNode(const T& data);

    void removeEdge(const T& start, const T& end);

    template <typename PrintFunc>
    void findShortestPath(const T& start, const T& end, PrintFunc printNode) const;

    template <typename PrintFunc>
    void displayGraph(PrintFunc printNode) const;

    template <typename Func>
    void forEachEdge(Func callback) const;
};

template <typename T>
Graph<T>::Graph()
{
}

template <typename T>
Graph<T>::~Graph()
{
}

template <typename T>
void Graph<T>::addNode(const T& data)
{
    Vertex v;
    v.data = data;
    vertices.addEnd(v);
}

template <typename T>
void Graph<T>::addEdge(const T& start, const T& end, int weight)
{
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.getAt(i).data == start) startIndex = i;
        if (vertices.getAt(i).data == end) endIndex = i;
    }

    if (startIndex != -1 && endIndex != -1)
    {
        Edge e;
        e.destinationIndex = endIndex;
        e.weight = weight;
        vertices.getAt(startIndex).adjacencyList.addEnd(e);

        Edge eReverse;
        eReverse.destinationIndex = startIndex;
        eReverse.weight = weight;
        vertices.getAt(endIndex).adjacencyList.addEnd(eReverse);
    }
    else
    {
        throw std::invalid_argument("Start or End node not found");
    }
}

template <typename T>
void Graph<T>::removeNode(const T& data)
{
    int removeIndex = -1;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.getAt(i).data == data)
        {
            removeIndex = i;
            break;
        }
    }

    if (removeIndex == -1) return;

    for (int i = 0; i < vertices.size(); i++)
    {
        if (i == removeIndex) continue;

        auto& adjList = vertices.getAt(i).adjacencyList;
        for (int j = 0; j < adjList.size(); j++)
        {
            if (adjList.getAt(j).destinationIndex == removeIndex)
            {
                adjList.removeAt(j);
                j--;
            }
            else if (adjList.getAt(j).destinationIndex > removeIndex)
            {
                adjList.getAt(j).destinationIndex--;
            }
        }
    }

    vertices.removeAt(removeIndex);
}

template <typename T>
void Graph<T>::removeEdge(const T& start, const T& end)
{
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices.getAt(i).data == start) startIndex = i;
        if (vertices.getAt(i).data == end) endIndex = i;
    }

    if (startIndex != -1 && endIndex != -1)
    {
        auto& startAdj = vertices.getAt(startIndex).adjacencyList;
        for (int i = 0; i < startAdj.size(); i++)
        {
            if (startAdj.getAt(i).destinationIndex == endIndex)
            {
                startAdj.removeAt(i);
                break;
            }
        }

        auto& endAdj = vertices.getAt(endIndex).adjacencyList;
        for (int i = 0; i < endAdj.size(); i++)
        {
            if (endAdj.getAt(i).destinationIndex == startIndex)
            {
                endAdj.removeAt(i);
                break;
            }
        }
    }
}

template <typename T>
template <typename PrintFunc>
void Graph<T>::findShortestPath(const T& start, const T& end, PrintFunc printNode) const
{
    int startIndex = -1, endIndex = -1;
    int numVertices = vertices.size();

    for (int i = 0; i < numVertices; i++)
    {
        if (vertices.getAt(i).data == start) startIndex = i;
        if (vertices.getAt(i).data == end) endIndex = i;
    }

    if (startIndex == -1 || endIndex == -1)
    {
        std::cout << "Path not found: nodes do not exist.\n";
        return;
    }

    int* distances = new int[numVertices];
    int* previous = new int[numVertices];
    bool* visited = new bool[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        distances[i] = INT_MAX;
        previous[i] = -1;
        visited[i] = false;
    }

    distances[startIndex] = 0;

    for (int count = 0; count < numVertices - 1; count++)
    {
        int u = -1;
        int minDistance = INT_MAX;

        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i] && distances[i] < minDistance)
            {
                minDistance = distances[i];
                u = i;
            }
        }

        if (u == -1 || distances[u] == INT_MAX) break;

        visited[u] = true;

        auto& adjList = vertices.getAt(u).adjacencyList;
        for (int j = 0; j < adjList.size(); j++)
        {
            int v = adjList.getAt(j).destinationIndex;
            int weight = adjList.getAt(j).weight;

            if (!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
            }
        }
    }

    if (distances[endIndex] == INT_MAX)
    {
        std::cout << "No path exists between the given stations.\n";
    }
    else
    {
        std::cout << "Shortest path distance: " << distances[endIndex] << "\n";

        int pathLen = 0;
        for (int at = endIndex; at != -1; at = previous[at]) pathLen++;

        int* path = new int[pathLen];
        int idx = pathLen - 1;
        for (int at = endIndex; at != -1; at = previous[at]) path[idx--] = at;

        std::cout << "Route: ";
        for (int i = 0; i < pathLen; i++)
        {
            printNode(vertices.getAt(path[i]).data);
            if (i < pathLen - 1) std::cout << " -> ";
        }
        std::cout << "\n";
        delete[] path;
    }

    delete[] distances;
    delete[] previous;
    delete[] visited;
}

template <typename T>
template <typename PrintFunc>
void Graph<T>::displayGraph(PrintFunc printNode) const
{
    if (vertices.isEmpty())
    {
        std::cout << "Graph is empty.\n";
        return;
    }

    for (int i = 0; i < vertices.size(); i++)
    {
        // Use the custom function to print the primary node
        printNode(vertices.getAt(i).data);
        std::cout << " connects to: ";

        const auto& adjList = vertices.getAt(i).adjacencyList;
        if (adjList.isEmpty())
        {
            std::cout << "(No tracks)\n";
            continue;
        }

        // Iterate through all connected edges
        for (int j = 0; j < adjList.size(); j++)
        {
            int destIdx = adjList.getAt(j).destinationIndex;

            // Use the custom function to print the destination node
            printNode(vertices.getAt(destIdx).data);
            std::cout << " [" << adjList.getAt(j).weight << " km]";

            if (j < adjList.size() - 1) std::cout << ",  ";
        }
        std::cout << "\n";
    }
}

template <typename T>
template <typename Func>
void Graph<T>::forEachEdge(Func callback) const
{
    for (int i = 0; i < vertices.size(); i++)
    {
        const T& startData = vertices.getAt(i).data;
        const auto& adjList = vertices.getAt(i).adjacencyList;
        for (int j = 0; j < adjList.size(); j++)
        {
            const T& endData = vertices.getAt(adjList.getAt(j).destinationIndex).data;
            callback(startData, endData, adjList.getAt(j).weight);
        }
    }
}

#endif

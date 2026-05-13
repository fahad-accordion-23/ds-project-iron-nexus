#include "../RailwayNetwork.hpp"

RailwayNetwork::RailwayNetwork()
{
    network = new Graph<Station*>();
    stationList = new CircularDoublyLinkedList<Station*>();
}

RailwayNetwork::~RailwayNetwork()
{
    delete network;
    delete stationList;
}

Station* RailwayNetwork::findStationById(Station::StationID id) const
{
    for (int i = 0; i < stationList->size(); i++)
    {
        if (stationList->getAt(i)->getId() == id)
        {
            return stationList->getAt(i);
        }
    }
    return nullptr;
}

void RailwayNetwork::addStation(Station* station)
{
    if (stationList->size() >= MAX_HUBS)
    {
        throw std::runtime_error("Maximum station capacity reached");
    }
    stationList->addEnd(station);
    network->addNode(station);
}

void RailwayNetwork::removeStation(Station::StationID id)
{
    Station* station = findStationById(id);
    if (station)
    {
        network->removeNode(station);
        for (int i = 0; i < stationList->size(); i++)
        {
            if (stationList->getAt(i)->getId() == id)
            {
                stationList->removeAt(i);
                break;
            }
        }
    }
}

void RailwayNetwork::connectStations(Station::StationID startId, Station::StationID endId,
                                     int distance)
{
    Station* start = findStationById(startId);
    Station* end = findStationById(endId);

    if (start && end)
    {
        network->addEdge(start, end, distance);
    }
}

void RailwayNetwork::disconnectStations(Station::StationID startId, Station::StationID endId)
{
    Station* start = findStationById(startId);
    Station* end = findStationById(endId);
    if (start && end)
    {
        network->removeEdge(start, end);
    }
}

void RailwayNetwork::findOptimalRoute(Station::StationID startId, Station::StationID endId)
{
    Station* start = findStationById(startId);
    Station* end = findStationById(endId);
    if (start && end)
    {
        network->findShortestPath(start, end,
                                  [](Station* st) { std::cout << "[" << st->getName() << "]"; });
    }
}
void RailwayNetwork::displayVisualMap() const
{
    if (!network) return;

    // Pass a lambda function that tells the graph HOW to print a Station*
    network->displayGraph(
        [](Station* st) { std::cout << "🚉 " << st->getName() << " (ID: " << st->getId() << ")"; });
}
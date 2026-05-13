#include "../StationRepository.hpp"

#include <fstream>
#include <sstream>

void StationRepository::saveToFile(const std::string& filename,
                                   const AVLTree<Station::StationID, Station*>* storage,
                                   const RailwayNetwork* network)
{
    if (!storage || !network) return;
    std::ofstream file(filename);
    if (!file.is_open()) return;

    // Save Stations
    storage->traverseInOrder([&file](Station::StationID id, Station* station)
                             { file << "STATION," << id << "," << station->getName() << "\n"; });

    // Save Tracks
    network->forEachTrack(
        [&file](Station* start, Station* end, int distance)
        {
            if (start->getId() < end->getId())
            {  // Prevent duplicates
                file << "TRACK," << start->getId() << "," << end->getId() << "," << distance
                     << "\n";
            }
        });
    file.close();
}

void StationRepository::loadFromFile(const std::string& filename,
                                     AVLTree<Station::StationID, Station*>* storage,
                                     RailwayNetwork* network)
{
    if (!storage || !network) return;
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        std::getline(ss, type, ',');

        if (type == "STATION")
        {
            std::string idStr, name;
            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            int id = std::stoi(idStr);

            Station* station = Station::Rehydrate(id, name);
            storage->insert(id, station);
            network->addStation(station);  // Re-add to network
        }
        else if (type == "TRACK")
        {
            std::string startStr, endStr, distStr;
            std::getline(ss, startStr, ',');
            std::getline(ss, endStr, ',');
            std::getline(ss, distStr, ',');

            network->connectStations(std::stoi(startStr), std::stoi(endStr), std::stoi(distStr));
        }
    }

    file.close();
}

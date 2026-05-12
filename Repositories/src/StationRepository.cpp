#include "../StationRepository.hpp"

#include <fstream>

void StationRepository::saveToFile(const std::string& filename,
                                   const AVLTree<Station::StationID, Station*>* storage)
{
    if (!storage) return;
    std::ofstream file(filename);
    if (!file.is_open()) return;

    storage->traverseInOrder([&file](Station::StationID id, Station* station)
                             { file << id << "," << station->getName() << "\n"; });

    file.close();
}

void StationRepository::loadFromFile(const std::string& filename,
                                     AVLTree<Station::StationID, Station*>* storage)
{
    if (!storage) return;
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        size_t comma = line.find(',');
        if (comma == std::string::npos) continue;

        int id = std::stoi(line.substr(0, comma));
        std::string name = line.substr(comma + 1);

        Station* station = Station::Rehydrate(id, name);
        storage->insert(id, station);
    }

    file.close();
}

#include "../StationRepository.hpp"
#include <fstream>
#include <iostream>

StationRepository::StationRepository()
{
    storage = new AVLTree<Station::StationID, Station*>();
}

StationRepository::~StationRepository()
{
    delete storage;
}

void StationRepository::add(Station* station)
{
    storage->insert(station->getId(), station);
}

void StationRepository::remove(Station::StationID id)
{
    storage->remove(id);
}

Station* StationRepository::find(Station::StationID id) const
{
    try {
        return storage->search(id);
    } catch (...) {
        return nullptr;
    }
}

int StationRepository::getCount() const
{
    int count = 0;
    storage->traverseInOrder([&count](Station::StationID, Station*) {
        count++;
    });
    return count;
}

void StationRepository::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) return;

    storage->traverseInOrder([&file](Station::StationID id, Station* station) {
        file << id << "," << station->getName() << "\n";
    });

    file.close();
}

void StationRepository::loadFromFile(const std::string& filename)
{
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

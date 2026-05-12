#include "../CoachRepository.hpp"
#include <fstream>
#include <iostream>

CoachRepository::CoachRepository()
{
    storage = new AVLTree<Coach::CoachID, Coach*>();
}

CoachRepository::~CoachRepository()
{
    delete storage;
}

void CoachRepository::add(Coach* coach)
{
    storage->insert(coach->getId(), coach);
}

void CoachRepository::remove(Coach::CoachID id)
{
    storage->remove(id);
}

Coach* CoachRepository::find(Coach::CoachID id) const
{
    try {
        return storage->search(id);
    } catch (...) {
        return nullptr;
    }
}

int CoachRepository::getCount() const
{
    int count = 0;
    storage->traverseInOrder([&count](Coach::CoachID, Coach*) {
        count++;
    });
    return count;
}

void CoachRepository::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) return;

    storage->traverseInOrder([&file](Coach::CoachID id, Coach* coach) {
        file << id << "," << coach->getName() << "," << coach->getCapacity() << "\n";
    });

    file.close();
}

void CoachRepository::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        size_t first = line.find(',');
        size_t second = line.find(',', first + 1);
        if (first == std::string::npos || second == std::string::npos) continue;

        int id = std::stoi(line.substr(0, first));
        std::string name = line.substr(first + 1, second - first - 1);
        int capacity = std::stoi(line.substr(second + 1));

        Coach* coach = Coach::Rehydrate(id, name, capacity);
        storage->insert(id, coach);
    }

    file.close();
}

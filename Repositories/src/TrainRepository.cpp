#include "../TrainRepository.hpp"
#include <fstream>
#include <iostream>

TrainRepository::TrainRepository()
{
    storage = new AVLTree<Train::TrainID, Train*>();
}

TrainRepository::~TrainRepository()
{
    delete storage;
}

void TrainRepository::add(Train* train)
{
    storage->insert(train->getId(), train);
}

void TrainRepository::remove(Train::TrainID id)
{
    storage->remove(id);
}

Train* TrainRepository::find(Train::TrainID id) const
{
    try {
        return storage->search(id);
    } catch (...) {
        return nullptr;
    }
}

int TrainRepository::getCount() const
{
    int count = 0;
    storage->traverseInOrder([&count](Train::TrainID, Train*) {
        count++;
    });
    return count;
}

void TrainRepository::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) return;

    storage->traverseInOrder([&file](Train::TrainID id, Train* train) {
        file << id << "," << train->getName() << "\n";
    });

    file.close();
}

void TrainRepository::loadFromFile(const std::string& filename)
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

        Train* train = Train::Rehydrate(id, name);
        storage->insert(id, train);
    }

    file.close();
}

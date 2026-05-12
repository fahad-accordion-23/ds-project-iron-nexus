#include "../TrainRepository.hpp"
#include <fstream>

void TrainRepository::saveToFile(const std::string& filename, const AVLTree<Train::TrainID, Train*>* storage)
{
    if (!storage) return;
    std::ofstream file(filename);
    if (!file.is_open()) return;

    storage->traverseInOrder([&file](Train::TrainID id, Train* train) {
        file << id << "," << train->getName() << "\n";
    });

    file.close();
}

void TrainRepository::loadFromFile(const std::string& filename, AVLTree<Train::TrainID, Train*>* storage)
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

        Train* train = Train::Rehydrate(id, name);
        storage->insert(id, train);
    }

    file.close();
}

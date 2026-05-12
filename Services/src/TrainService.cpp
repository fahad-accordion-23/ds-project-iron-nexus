#include "../TrainService.hpp"

#include <iostream>

#include "../../Repositories/TrainRepository.hpp"

TrainService::TrainService()
{
    trainRegistry = new AVLTree<Train::TrainID, Train*>();
}

TrainService::~TrainService()
{
    // Clean up all trains in the registry
    trainRegistry->traverseInOrder([](Train::TrainID, Train* train) { delete train; });
    delete trainRegistry;
}

void TrainService::registerTrain(const std::string& name)
{
    Train* train = Train::Register(name);
    trainRegistry->insert(train->getId(), train);
    std::cout << "[TrainService] Registered train '" << name << "' with ID: " << train->getId()
              << "\n";
}

void TrainService::removeTrain(Train::TrainID id)
{
    try
    {
        Train* train = trainRegistry->search(id);
        trainRegistry->remove(id);
        std::cout << "[TrainService] Decommissioned train '" << train->getName() << "' (ID: " << id
                  << ")\n";
        delete train;
    }
    catch (...)
    {
        std::cout << "[TrainService] Error: Train ID " << id << " not found.\n";
    }
}

Train* TrainService::findTrain(Train::TrainID id)
{
    try
    {
        return trainRegistry->search(id);
    }
    catch (...)
    {
        return nullptr;
    }
}

void TrainService::listAllTrains() const
{
    std::cout << "\n========== FLEET REGISTRY ==========\n";

    int count = 0;
    trainRegistry->traverseInOrder(
        [&count](Train::TrainID id, Train* train)
        {
            std::cout << "  [" << id << "] " << train->getName() << "\n";
            count++;
        });

    if (count == 0)
    {
        std::cout << "  (No trains registered)\n";
    }

    std::cout << "  Total: " << count << " train(s)\n";
    std::cout << "====================================\n";
}

void TrainService::emergencyStop(Train::TrainID id)
{
    Train* train = findTrain(id);
    if (train)
    {
        std::cout << "[EMERGENCY] Train '" << train->getName() << "' (ID: " << id
                  << ") has been STOPPED.\n";
    }
    else
    {
        std::cout << "[EMERGENCY] Error: Train ID " << id << " not found.\n";
    }
}

void TrainService::saveData(const std::string& filename) const
{
    TrainRepository::saveToFile(filename, trainRegistry);
}

void TrainService::loadData(const std::string& filename)
{
    TrainRepository::loadFromFile(filename, trainRegistry);
}

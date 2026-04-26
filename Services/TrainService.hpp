#ifndef TRAIN_SERVICE_HPP
#define TRAIN_SERVICE_HPP

#include <string>
#include "../Train/Train.hpp"
#include "../Structures/AVLTree.hpp"

/**
 * @brief Application service for managing the Train Registry (Module 1).
 * Owns the master AVL tree of all active trains in the system.
 */
class TrainService
{
private:
    // Self-balancing hierarchy for consistent O(log N) operations on 10,000+ trains.
    AVLTree<Train::TrainID, Train*>* trainRegistry;

public:
    TrainService();
    ~TrainService();

    /**
     * @brief Register a new train to the fleet.
     */
    void registerTrain(const std::string& name);

    /**
     * @brief Decommission a train.
     */
    void removeTrain(Train::TrainID id);

    /**
     * @brief Find a specific train for commands or composition updates.
     */
    Train* findTrain(Train::TrainID id);

    /**
     * @brief Perform an 'In-Order' traversal of the registry to list all trains.
     */
    void listAllTrains() const;

    /**
     * @brief Instant command to stop a specific train (Module 1 requirement).
     */
    void emergencyStop(Train::TrainID id);
};

#endif // TRAIN_SERVICE_HPP

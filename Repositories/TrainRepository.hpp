#ifndef TRAIN_REPOSITORY_HPP
#define TRAIN_REPOSITORY_HPP

#include "../Train/Train.hpp"
#include "../Structures/AVLTree.hpp"

/**
 * @brief Data Access Layer for managing the Train fleet.
 */
class TrainRepository
{
private:
    AVLTree<Train::TrainID, Train*>* storage;

public:
    TrainRepository();
    ~TrainRepository();

    void add(Train* train);
    void remove(Train::TrainID id);
    Train* find(Train::TrainID id) const;
    void getAll(void (*callback)(Train::TrainID, Train*)) const;
    
    int getCount() const;
};

#endif // TRAIN_REPOSITORY_HPP

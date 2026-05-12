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
    template<typename Func>
    void getAll(Func callback) const { storage->traverseInOrder(callback); }
    
    int getCount() const;

    /**
     * @brief Save all trains to a file.
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Load trains from a file.
     */
    void loadFromFile(const std::string& filename);
};

#endif // TRAIN_REPOSITORY_HPP

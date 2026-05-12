#ifndef TRAIN_REPOSITORY_HPP
#define TRAIN_REPOSITORY_HPP

#include <string>
#include "../Train/Train.hpp"
#include "../Structures/AVLTree.hpp"

/**
 * @brief Stateless utility for Train fleet persistence.
 */
class TrainRepository
{
public:
    /**
     * @brief Save all trains in the provided registry to a file.
     */
    static void saveToFile(const std::string& filename, const AVLTree<Train::TrainID, Train*>* storage);

    /**
     * @brief Load trains from a file into the provided registry.
     */
    static void loadFromFile(const std::string& filename, AVLTree<Train::TrainID, Train*>* storage);
};

#endif // TRAIN_REPOSITORY_HPP

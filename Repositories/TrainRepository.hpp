#ifndef TRAIN_REPOSITORY_HPP
#define TRAIN_REPOSITORY_HPP

#include <string>

#include "../Structures/AVLTree.hpp"
#include "../Train/Train.hpp"

class TrainRepository
{
public:
    static void saveToFile(const std::string& filename,
                           const AVLTree<Train::TrainID, Train*>* storage);

    static void loadFromFile(const std::string& filename, AVLTree<Train::TrainID, Train*>* storage);
};

#endif

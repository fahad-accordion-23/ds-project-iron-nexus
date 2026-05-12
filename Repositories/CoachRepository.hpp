#ifndef COACH_REPOSITORY_HPP
#define COACH_REPOSITORY_HPP

#include <string>

#include "../Structures/AVLTree.hpp"
#include "../Train/Coach.hpp"

class CoachRepository
{
public:
    static void saveToFile(const std::string& filename,
                           const AVLTree<Coach::CoachID, Coach*>* storage);
    static void loadFromFile(const std::string& filename, AVLTree<Coach::CoachID, Coach*>* storage);
};

#endif

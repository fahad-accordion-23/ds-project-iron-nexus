#ifndef COACH_REPOSITORY_HPP
#define COACH_REPOSITORY_HPP

#include "../Train/Coach.hpp"
#include "../Structures/AVLTree.hpp"

/**
 * @brief Data Access Layer for managing the Global Coach Registry.
 */
class CoachRepository
{
private:
    AVLTree<Coach::CoachID, Coach*>* storage;

public:
    CoachRepository();
    ~CoachRepository();

    void add(Coach* coach);
    void remove(Coach::CoachID id);
    Coach* find(Coach::CoachID id) const;
    
    int getCount() const;

    /**
     * @brief Save all coaches to a file.
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Load coaches from a file.
     */
    void loadFromFile(const std::string& filename);
};

#endif // COACH_REPOSITORY_HPP

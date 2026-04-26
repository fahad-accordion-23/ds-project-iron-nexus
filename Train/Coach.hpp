#ifndef COACH_HPP
#define COACH_HPP

#include <string>

/**
 * @brief Represents a Coach in a Train.
 *
 * In the finalized architecture, the Coach acts as a metadata container.
 * Physical seats and their indexing are managed centrally by the Train.
 */
class Coach
{
public:
    using CoachID = int;

private:
    static CoachID nextId;

    const CoachID id;
    std::string name;
    int capacity;

    /**
     * @brief Private constructor for internal use by factory methods.
     */
    Coach(CoachID coachId, const std::string& coachName, int coachCapacity);

public:
    static Coach* Register(const std::string& name, int capacity);
    static Coach* Rehydrate(CoachID id, const std::string& name, int capacity);
    ~Coach();

    CoachID getId() const;
    std::string getName() const;
    int getCapacity() const;
};

#endif  // COACH_HPP

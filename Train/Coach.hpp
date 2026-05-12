#ifndef COACH_HPP
#define COACH_HPP

#include <string>

class Coach
{
public:
    using CoachID = int;

private:
    static CoachID nextId;

    const CoachID id;
    std::string name;
    int capacity;

    Coach(CoachID coachId, const std::string& coachName, int coachCapacity);

public:
    static Coach* Register(const std::string& name, int capacity);
    static Coach* Rehydrate(CoachID id, const std::string& name, int capacity);
    ~Coach();

    CoachID getId() const;
    std::string getName() const;
    int getCapacity() const;
};

#endif

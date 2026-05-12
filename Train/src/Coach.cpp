#include "../Coach.hpp"

Coach::CoachID Coach::nextId = 2000;

Coach::Coach(CoachID coachId, const std::string& coachName, int coachCapacity)
    : id(coachId), name(coachName), capacity(coachCapacity)
{
}

Coach* Coach::Register(const std::string& name, int capacity) { return new Coach(nextId++, name, capacity); }
Coach* Coach::Rehydrate(CoachID id, const std::string& name, int capacity) { return new Coach(id, name, capacity); }
Coach::~Coach() {}
Coach::CoachID Coach::getId() const { return id; }
std::string Coach::getName() const { return name; }
int Coach::getCapacity() const { return capacity; }

#include "../CoachRepository.hpp"

CoachRepository::CoachRepository() : storage(nullptr) {}
CoachRepository::~CoachRepository() {}
void CoachRepository::add(Coach* coach) {}
void CoachRepository::remove(Coach::CoachID id) {}
Coach* CoachRepository::find(Coach::CoachID id) const { return nullptr; }
int CoachRepository::getCount() const { return 0; }

#include "../StationRepository.hpp"

StationRepository::StationRepository() : storage(nullptr) {}
StationRepository::~StationRepository() {}
void StationRepository::add(Station* station) {}
void StationRepository::remove(Station::StationID id) {}
Station* StationRepository::find(Station::StationID id) const { return nullptr; }
void StationRepository::getAll(void (*callback)(Station::StationID, Station*)) const {}
int StationRepository::getCount() const { return 0; }

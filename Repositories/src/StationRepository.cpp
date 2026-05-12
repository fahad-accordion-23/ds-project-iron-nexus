#include "../StationRepository.hpp"

StationRepository::StationRepository() : storage(nullptr) {}
StationRepository::~StationRepository() {}
void StationRepository::add(Station* station) {}
void StationRepository::remove(Station::StationID id) {}
Station* StationRepository::find(Station::StationID id) const { return nullptr; }
int StationRepository::getCount() const { return 0; }
void StationRepository::saveToFile(const std::string& filename) const {}
void StationRepository::loadFromFile(const std::string& filename) {}

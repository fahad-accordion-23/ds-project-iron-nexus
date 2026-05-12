#include "../ScheduleRepository.hpp"

ScheduleRepository::ScheduleRepository() : storage(nullptr) {}
ScheduleRepository::~ScheduleRepository() {}
void ScheduleRepository::setAssignment(Train::TrainID trainId, Station::StationID stationId) {}
void ScheduleRepository::removeAssignment(Train::TrainID trainId) {}
Station::StationID ScheduleRepository::getAssignment(Train::TrainID trainId) const { return -1; }
bool ScheduleRepository::hasAssignment(Train::TrainID trainId) const { return false; }
void ScheduleRepository::saveToFile(const std::string& filename) const {}
void ScheduleRepository::loadFromFile(const std::string& filename) {}

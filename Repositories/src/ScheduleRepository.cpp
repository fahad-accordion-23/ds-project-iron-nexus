#include "../ScheduleRepository.hpp"
#include <fstream>
#include <iostream>

ScheduleRepository::ScheduleRepository()
{
    storage = new HashTable<Train::TrainID, Station::StationID>();
}

ScheduleRepository::~ScheduleRepository()
{
    delete storage;
}

void ScheduleRepository::setAssignment(Train::TrainID trainId, Station::StationID stationId)
{
    storage->insert(trainId, stationId);
}

void ScheduleRepository::removeAssignment(Train::TrainID trainId)
{
    storage->remove(trainId);
}

Station::StationID ScheduleRepository::getAssignment(Train::TrainID trainId) const
{
    try {
        return storage->search(trainId);
    } catch (...) {
        return -1;
    }
}

bool ScheduleRepository::hasAssignment(Train::TrainID trainId) const
{
    try {
        storage->search(trainId);
        return true;
    } catch (...) {
        return false;
    }
}

void ScheduleRepository::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) return;

    storage->forEach([&file](Train::TrainID trainId, Station::StationID stationId) {
        file << trainId << "," << stationId << "\n";
    });

    file.close();
}

void ScheduleRepository::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        size_t comma = line.find(',');
        if (comma == std::string::npos) continue;

        int trainId = std::stoi(line.substr(0, comma));
        int stationId = std::stoi(line.substr(comma + 1));

        storage->insert(trainId, stationId);
    }

    file.close();
}

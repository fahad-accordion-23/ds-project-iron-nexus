#include "../ScheduleRepository.hpp"

#include <fstream>

void ScheduleRepository::saveToFile(const std::string& filename,
                                    const HashTable<Train::TrainID, Station::StationID>* storage)
{
    if (!storage) return;

    std::ofstream file(filename);
    if (!file.is_open()) return;

    storage->forEach([&file](Train::TrainID trainId, Station::StationID stationId)
                     { file << trainId << "," << stationId << "\n"; });

    file.close();
}

void ScheduleRepository::loadFromFile(const std::string& filename,
                                      HashTable<Train::TrainID, Station::StationID>* storage)
{
    if (!storage) return;

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

#ifndef SCHEDULE_REPOSITORY_HPP
#define SCHEDULE_REPOSITORY_HPP

#include <string>

#include "../Railway/Station.hpp"
#include "../Structures/HashTable.hpp"
#include "../Train/Train.hpp"

/**
 * @brief Stateless utility for train-to-route assignment persistence.
 */
class ScheduleRepository
{
public:
    static void saveToFile(const std::string& filename,
                           const HashTable<Train::TrainID, Station::StationID>* storage);
    static void loadFromFile(const std::string& filename,
                             HashTable<Train::TrainID, Station::StationID>* storage);
};

#endif  // SCHEDULE_REPOSITORY_HPP

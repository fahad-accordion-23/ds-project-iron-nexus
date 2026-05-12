#ifndef SCHEDULE_REPOSITORY_HPP
#define SCHEDULE_REPOSITORY_HPP

#include "../Train/Train.hpp"
#include "../Railway/Station.hpp"
#include "../Structures/HashTable.hpp"

/**
 * @brief Data Access Layer for managing train-to-route assignments.
 */
class ScheduleRepository
{
private:
    HashTable<Train::TrainID, Station::StationID>* storage;

public:
    ScheduleRepository();
    ~ScheduleRepository();

    void setAssignment(Train::TrainID trainId, Station::StationID stationId);
    void removeAssignment(Train::TrainID trainId);
    Station::StationID getAssignment(Train::TrainID trainId) const;
    
    bool hasAssignment(Train::TrainID trainId) const;

    /**
     * @brief Save current schedule to a file.
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Load schedule from a file.
     */
    void loadFromFile(const std::string& filename);
};

#endif // SCHEDULE_REPOSITORY_HPP

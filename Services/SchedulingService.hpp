#ifndef SCHEDULING_SERVICE_HPP
#define SCHEDULING_SERVICE_HPP

#include "../Railway/Station.hpp"
#include "../Structures/HashTable.hpp"
#include "../Train/Train.hpp"

/**
 * @brief Application service for assigning trains to specific routes in the network.
 * Links Module 1 (Trains) and Module 3 (Network).
 */
class SchedulingService
{
private:
    // Maps TrainID to its current route destination or path details
    // For now, let's store the destination StationID as a simple assignment
    HashTable<Train::TrainID, Station::StationID>* schedule;

public:
    SchedulingService();
    ~SchedulingService();

    /**
     * @brief Assign a train to a specific route between two stations.
     */
    void assignRoute(Train::TrainID trainId, Station::StationID startId, Station::StationID endId);

    /**
     * @brief Clear a train's current assignment.
     */
    void decommissionRoute(Train::TrainID trainId);

    /**
     * @brief Get the current destination of a train.
     */
    Station::StationID getDestination(Train::TrainID trainId) const;

    void showSchedule() const;

    /**
     * @brief Persistence delegation
     */
    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);
};

#endif  // SCHEDULING_SERVICE_HPP

#ifndef STATION_REPOSITORY_HPP
#define STATION_REPOSITORY_HPP

#include "../Railway/Station.hpp"
#include "../Structures/AVLTree.hpp"

/**
 * @brief Data Access Layer for managing Stations in the network.
 */
class StationRepository
{
private:
    AVLTree<Station::StationID, Station*>* storage;

public:
    StationRepository();
    ~StationRepository();

    void add(Station* station);
    void remove(Station::StationID id);
    Station* find(Station::StationID id) const;
    void getAll(void (*callback)(Station::StationID, Station*)) const;
    
    int getCount() const;
};

#endif // STATION_REPOSITORY_HPP

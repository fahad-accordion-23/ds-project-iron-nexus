#ifndef STATION_REPOSITORY_HPP
#define STATION_REPOSITORY_HPP

#include <string>

#include "../Railway/Station.hpp"
#include "../Structures/AVLTree.hpp"

class StationRepository
{
public:
    static void saveToFile(const std::string& filename,
                           const AVLTree<Station::StationID, Station*>* storage);
    static void loadFromFile(const std::string& filename,
                             AVLTree<Station::StationID, Station*>* storage);
};

#endif

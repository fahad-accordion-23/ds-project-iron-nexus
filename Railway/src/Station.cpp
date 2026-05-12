#include "../Station.hpp"

Station::StationID Station::nextId = 3000; // Starting ID for stations

Station::Station(StationID id, const std::string& name) : id(id), name(name) {}

Station* Station::Register(const std::string& name)
{
    return new Station(nextId++, name);
}

Station* Station::Rehydrate(StationID id, const std::string& name)
{
    if (id >= nextId) nextId = id + 1;
    return new Station(id, name);
}

Station::StationID Station::getId() const { return id; }
std::string Station::getName() const { return name; }
void Station::setName(const std::string& newName) { name = newName; }

bool Station::operator==(const Station& other) const
{
    return this->id == other.id;
}

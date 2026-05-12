#ifndef STATION_HPP
#define STATION_HPP

#include <string>

/**
 * @brief Represents a Station (Vertex) in the Railway Network.
 */
class Station
{
public:
    using StationID = int;

private:
    static StationID nextId;
    const StationID id;
    std::string name;

    Station(StationID id, const std::string& name);

public:
    static Station* Register(const std::string& name);
    static Station* Rehydrate(StationID id, const std::string& name);

    StationID getId() const;
    std::string getName() const;
    void setName(const std::string& newName);

    bool operator==(const Station& other) const;
};

#endif // STATION_HPP

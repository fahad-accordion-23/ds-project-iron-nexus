#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <string>

#include "../Structures/BST.hpp"
#include "../Structures/CircularDoublyLinkedList.hpp"
#include "../Structures/HashTable.hpp"
#include "Coach.hpp"
#include "Seat.hpp"

/**
 * @brief Represents a Train in the Iron Nexus Railway Management System.
 *
 * Each train manages its own composition and a centralized seating repository.
 */
class Train
{
public:
    using TrainID = int;

private:
    static TrainID nextId;

    const TrainID id;
    std::string name;

    CircularDoublyLinkedList<Coach>* coaches;
    bool isReversed;

    // Seating Repository: Centralized for efficiency and synchronization
    HashTable<Seat::GlobalSeatNumber, Seat*>* seatLookup;
    BST<Seat::GlobalSeatNumber, Seat*>* seatTree;

    // Metadata-Based Sizing for O(1) buffer logic
    int currentSeatSize;
    int totalSeatCapacity;

    Train(TrainID trainId, const std::string& trainName);

public:
    static Train* Register(const std::string& name);
    static Train* Rehydrate(TrainID id, const std::string& name);
    ~Train();

    TrainID getId() const;
    std::string getName() const;
    void setName(const std::string& trainName);

    CircularDoublyLinkedList<Coach>* getCoaches() const;

    void addCoachFront(Coach* coach);
    void addCoachEnd(Coach* coach);
    void insertCoach(Coach* coach, int position);
    Coach* removeCoach(int position);
    void reverseOrientation();

    Seat* findSeat(Seat::GlobalSeatNumber globalNumber);
    bool bookSeat(Seat::GlobalSeatNumber globalNumber);
    bool releaseSeat(Seat::GlobalSeatNumber globalNumber);
    BST<Seat::GlobalSeatNumber, Seat*>* getSeatingChart() const;
};

#endif  // TRAIN_HPP

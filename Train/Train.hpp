#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <string>

#include "../Structures/BST.hpp"
#include "../Structures/CircularDoublyLinkedList.hpp"
#include "../Structures/HashTable.hpp"
#include "Coach.hpp"
#include "Seat.hpp"

class Train
{
public:
    using TrainID = int;

private:
    static TrainID nextId;

    const TrainID id;
    std::string name;

    CircularDoublyLinkedList<Coach*>* coaches;
    bool isReversed;

    HashTable<Seat::GlobalSeatNumber, Seat*>* seatLookup;
    BST<Seat::GlobalSeatNumber, Seat*>* seatTree;

    int currentSeatSize;
    int totalSeatCapacity;

    Train(TrainID trainId, const std::string& trainName);

    void rebuildSeats();

public:
    static Train* Register(const std::string& name);
    static Train* Rehydrate(TrainID id, const std::string& name);
    ~Train();

    TrainID getId() const;
    std::string getName() const;
    void setName(const std::string& trainName);

    CircularDoublyLinkedList<Coach*>* getCoaches() const;

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

#endif

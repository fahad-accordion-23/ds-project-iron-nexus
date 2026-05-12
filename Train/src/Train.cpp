#include "../Train.hpp"

Train::TrainID Train::nextId = 1000;

Train::Train(TrainID trainId, const std::string& trainName)
    : id(trainId), name(trainName), coaches(nullptr), isReversed(false),
      seatLookup(nullptr), seatTree(nullptr), currentSeatSize(0), totalSeatCapacity(0)
{
}

Train* Train::Register(const std::string& name) { return new Train(nextId++, name); }
Train* Train::Rehydrate(TrainID id, const std::string& name) { return new Train(id, name); }
Train::~Train() {}
Train::TrainID Train::getId() const { return id; }
std::string Train::getName() const { return name; }
void Train::setName(const std::string& trainName) { name = trainName; }
CircularDoublyLinkedList<Coach>* Train::getCoaches() const { return coaches; }
void Train::addCoachFront(Coach* coach) {}
void Train::addCoachEnd(Coach* coach) {}
void Train::insertCoach(Coach* coach, int position) {}
Coach* Train::removeCoach(int position) { return nullptr; }
void Train::reverseOrientation() { isReversed = !isReversed; }
Seat* Train::findSeat(Seat::GlobalSeatNumber globalNumber) { return nullptr; }
bool Train::bookSeat(Seat::GlobalSeatNumber globalNumber) { return false; }
bool Train::releaseSeat(Seat::GlobalSeatNumber globalNumber) { return false; }
BST<Seat::GlobalSeatNumber, Seat*>* Train::getSeatingChart() const { return seatTree; }

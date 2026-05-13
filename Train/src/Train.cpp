#include "../Train.hpp"

Train::TrainID Train::nextId = 1000;

Train::Train(TrainID trainId, const std::string& trainName)
    : id(trainId), name(trainName), isReversed(false), currentSeatSize(0), totalSeatCapacity(0)
{
    coaches = new CircularDoublyLinkedList<Coach*>();
    seatLookup = new HashTable<Seat::GlobalSeatNumber, Seat*>(200);
    seatTree = new BST<Seat::GlobalSeatNumber, Seat*>();
}

void Train::rebuildSeats()
{
    if (seatTree != nullptr && !seatTree->isEmpty())
    {
        seatTree->traverseInOrder([](Seat::GlobalSeatNumber, Seat* seat) { delete seat; });

        seatTree->clear();
        seatLookup->clear();
    }

    totalSeatCapacity = 0;
    if (!coaches->isEmpty())
    {
        for (int i = 0; i < coaches->size(); i++)
        {
            totalSeatCapacity += coaches->getAt(i)->getCapacity();
        }
    }
    currentSeatSize = totalSeatCapacity;

    for (int i = 1; i <= totalSeatCapacity; i++)
    {
        Seat* s = new Seat(i);
        seatLookup->insert(i, s);
        seatTree->insert(i, s);
    }
}

Train* Train::Register(const std::string& name)
{
    return new Train(nextId++, name);
}

Train* Train::Rehydrate(TrainID id, const std::string& name)
{
    if (id >= nextId) nextId = id + 1;
    return new Train(id, name);
}

Train::~Train()
{
    if (seatTree != nullptr)
    {
        seatTree->traverseInOrder([](Seat::GlobalSeatNumber, Seat* seat) { delete seat; });
    }

    delete coaches;
    delete seatLookup;
    delete seatTree;
}

Train::TrainID Train::getId() const
{
    return id;
}
std::string Train::getName() const
{
    return name;
}
void Train::setName(const std::string& trainName)
{
    name = trainName;
}

CircularDoublyLinkedList<Coach*>* Train::getCoaches() const
{
    return coaches;
}

void Train::addCoachFront(Coach* coach)
{
    coaches->addFront(coach);
    rebuildSeats();
}

void Train::addCoachEnd(Coach* coach)
{
    coaches->addEnd(coach);
    rebuildSeats();
}

void Train::insertCoach(Coach* coach, int position)
{
    coaches->insertAt(coach, position);
    rebuildSeats();
}

Coach* Train::removeCoach(int position)
{
    if (position < 0 || position >= coaches->size()) return nullptr;

    Coach* coach = coaches->getAt(position);
    coaches->removeAt(position);

    rebuildSeats();

    return coach;
}

void Train::reverseOrientation()
{
    isReversed = !isReversed;
    coaches->reverse();
}

Seat* Train::findSeat(Seat::GlobalSeatNumber globalNumber)
{
    try
    {
        return seatLookup->search(globalNumber);
    }
    catch (...)
    {
        return nullptr;
    }
}

bool Train::bookSeat(Seat::GlobalSeatNumber globalNumber)
{
    Seat* s = findSeat(globalNumber);
    if (s && s->getStatus() == SeatStatus::Available)
    {
        s->setStatus(SeatStatus::Booked);
        return true;
    }
    return false;
}

bool Train::releaseSeat(Seat::GlobalSeatNumber globalNumber)
{
    Seat* s = findSeat(globalNumber);
    if (s && s->getStatus() == SeatStatus::Booked)
    {
        s->setStatus(SeatStatus::Available);
        return true;
    }
    return false;
}

BST<Seat::GlobalSeatNumber, Seat*>* Train::getSeatingChart() const
{
    return seatTree;
}

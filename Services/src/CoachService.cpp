#include "../CoachService.hpp"

#include <iostream>

#include "../../Repositories/CoachRepository.hpp"

CoachService::CoachService(TrainService* ts) : trainService(ts)
{
    coachRegistry = new AVLTree<Coach::CoachID, Coach*>();
}

CoachService::~CoachService()
{
    coachRegistry->traverseInOrder([](Coach::CoachID, Coach* coach) { delete coach; });
    delete coachRegistry;
}

Coach::CoachID CoachService::createCoach(const std::string& coachName, int capacity)
{
    Coach* coach = Coach::Register(coachName, capacity);
    coachRegistry->insert(coach->getId(), coach);
    std::cout << "[CoachService] Standalone Coach '" << coachName
              << "' created with ID: " << coach->getId() << " and Capacity: " << capacity << ".\n";
    return coach->getId();
}

void CoachService::rehydrateCoach(Coach::CoachID id, const std::string& name, int capacity)
{
    Coach* coach = Coach::Rehydrate(id, name, capacity);
    coachRegistry->insert(id, coach);
}

void CoachService::deleteCoach(Coach::CoachID coachId)
{
    Coach* coach = coachRegistry->search(coachId);

    if (coach->getIsAttached())
    {
        std::cout << "[CoachService] Error: Cannot delete Coach " << coachId
                  << ". It is currently attached to a train. Unlink it first.\n";
        return;
    }

    coachRegistry->remove(coachId);
    std::cout << "[CoachService] Coach '" << coach->getName() << "' deleted.\n";
    delete coach;
}

void CoachService::linkCoach(Coach::CoachID coachId, Train::TrainID trainId, int index)
{
    Train* train = trainService->findTrain(trainId);
    if (!train)
    {
        std::cout << "[CoachService] Error: Train ID " << trainId << " not found.\n";
        return;
    }

    // === INVARIANT FIX 1: Prevent modifying a train with active bookings ===
    bool hasBookings = false;
    if (train->getSeatingChart())
    {
        train->getSeatingChart()->traverseInOrder(
            [&hasBookings](Seat::GlobalSeatNumber, Seat* seat)
            {
                if (seat->getStatus() == SeatStatus::Booked) hasBookings = true;
            });
    }
    if (hasBookings)
    {
        std::cout << "[CoachService] Error: Cannot modify train structure while passengers are "
                     "booked. Cancel all bookings first.\n";
        return;
    }

    try
    {
        Coach* coach = coachRegistry->search(coachId);

        // ==============================================================
        // INVARIANT CHECK: Prevent a coach from being linked multiple times
        // ==============================================================
        if (coach->getIsAttached())
        {
            std::cout << "[CoachService] Error: Coach " << coachId
                      << " is already attached to a train. Unlink it first.\n";
            return;
        }
        // ==============================================================

        if (index == 0)
        {
            train->addCoachFront(coach);
        }
        else if (index == -1)
        {
            train->addCoachEnd(coach);
        }
        else
        {
            train->insertCoach(coach, index);
        }

        std::cout << "[CoachService] Coach '" << coach->getName() << "' (ID: " << coach->getId()
                  << ") linked to Train " << trainId << ".\n";

        // Mark it as actively in use!
        coach->setIsAttached(true);
    }
    catch (...)
    {
        std::cout << "[CoachService] Error: Coach ID " << coachId << " not found.\n";
    }
}

void CoachService::unlinkCoach(Coach::CoachID coachId, Train::TrainID trainId)
{
    Train* train = trainService->findTrain(trainId);
    if (!train)
    {
        std::cout << "[CoachService] Error: Train ID " << trainId << " not found.\n";
        return;
    }

    // === INVARIANT FIX 1: Prevent modifying a train with active bookings ===
    bool hasBookings = false;
    if (train->getSeatingChart())
    {
        train->getSeatingChart()->traverseInOrder(
            [&hasBookings](Seat::GlobalSeatNumber, Seat* seat)
            {
                if (seat->getStatus() == SeatStatus::Booked) hasBookings = true;
            });
    }
    if (hasBookings)
    {
        std::cout << "[CoachService] Error: Cannot modify train structure while passengers are "
                     "booked. Cancel all bookings first.\n";
        return;
    }

    auto* coaches = train->getCoaches();
    int position = -1;
    for (int i = 0; i < coaches->size(); i++)
    {
        if (coaches->getAt(i)->getId() == coachId)
        {
            position = i;
            break;
        }
    }

    if (position == -1)
    {
        std::cout << "[CoachService] Error: Coach ID " << coachId << " not found on Train "
                  << trainId << ".\n";
        return;
    }

    Coach* removed = train->removeCoach(position);
    if (removed)
    {
        std::cout << "[CoachService] Coach '" << removed->getName() << "' unlinked from Train "
                  << trainId << ".\n";

        removed->setIsAttached(false);
    }
}

void CoachService::listAllCoaches() const
{
    std::cout << "\n========== COACH REGISTRY ==========\n";
    if (!coachRegistry)
    {
        std::cout << "  (No coaches registered)\n";
    }
    else
    {
        int total = 0;
        coachRegistry->traverseInOrder(
            [&total](Coach::CoachID id, Coach* coach)
            {
                std::cout << "  [" << id << "] " << coach->getName()
                          << " (Capacity: " << coach->getCapacity() << ")\n";
                total++;
            });

        if (total == 0)
        {
            std::cout << "  (No coaches registered)\n";
        }
        std::cout << "  Total: " << total << " coach(es)\n";
    }
    std::cout << "====================================\n";
}

void CoachService::reverseTrain(Train::TrainID trainId)
{
    Train* train = trainService->findTrain(trainId);
    if (!train)
    {
        std::cout << "[CoachService] Error: Train ID " << trainId << " not found.\n";
        return;
    }

    // === INVARIANT FIX 1: Prevent modifying a train with active bookings ===
    bool hasBookings = false;
    if (train->getSeatingChart())
    {
        train->getSeatingChart()->traverseInOrder(
            [&hasBookings](Seat::GlobalSeatNumber, Seat* seat)
            {
                if (seat->getStatus() == SeatStatus::Booked) hasBookings = true;
            });
    }
    if (hasBookings)
    {
        std::cout << "[CoachService] Error: Cannot modify train structure while passengers are "
                     "booked. Cancel all bookings first.\n";
        return;
    }

    train->reverseOrientation();
    std::cout << "[CoachService] Train " << trainId << " orientation reversed.\n";
}

void CoachService::traverseTrain(Train::TrainID trainId) const
{
    Train* train = trainService->findTrain(trainId);
    if (!train) return;

    auto* coaches = train->getCoaches();
    bool rev = train->getIsReversed();  // Check orientation

    std::cout << "\n========== TRAIN " << trainId << " WALKTHROUGH ==========\n";
    std::cout << "[Engine: " << train->getName() << "]";

    if (coaches->isEmpty())
    {
        std::cout << " -> (No coaches attached)\n";
    }
    else
    {
        for (int i = 0; i < coaches->size(); i++)
        {
            // OPTIMIZATION: Calculate logical index
            int idx = rev ? (coaches->size() - 1 - i) : i;
            Coach* c = coaches->getAt(idx);
            std::cout << " <-> [Coach " << c->getId() << ": " << c->getName() << "]";
        }
        std::cout << "\n";
    }
    std::cout << "===============================================\n";
}

bool CoachService::bookSeat(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber)
{
    Train* train = trainService->findTrain(trainId);
    if (!train) return false;

    bool result = train->bookSeat(seatNumber);
    if (result)
    {
        std::cout << "[CoachService] Seat " << seatNumber << " booked on Train " << trainId
                  << ".\n";
    }
    else
    {
        std::cout << "[CoachService] Seat " << seatNumber << " unavailable on Train " << trainId
                  << ".\n";
    }
    return result;
}

bool CoachService::cancelBooking(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber)
{
    Train* train = trainService->findTrain(trainId);
    if (!train) return false;

    bool result = train->releaseSeat(seatNumber);
    if (result)
    {
        std::cout << "[CoachService] Seat " << seatNumber << " released on Train " << trainId
                  << ".\n";
    }
    return result;
}

SeatStatus CoachService::checkSeatStatus(Train::TrainID trainId,
                                         Seat::GlobalSeatNumber seatNumber) const
{
    Train* train = trainService->findTrain(trainId);
    if (!train) return SeatStatus::Available;

    Seat* seat = train->findSeat(seatNumber);
    if (seat) return seat->getStatus();
    return SeatStatus::Available;
}

void CoachService::viewSeatingChart(Train::TrainID trainId) const
{
    Train* train = trainService->findTrain(trainId);
    if (!train)
    {
        std::cout << "[CoachService] Error: Train ID " << trainId << " not found.\n";
        return;
    }

    std::cout << "\n========== SEATING CHART: Train " << trainId << " ==========\n";
    auto* chart = train->getSeatingChart();
    chart->traverseInOrder(
        [](Seat::GlobalSeatNumber num, Seat* seat)
        {
            std::cout << "  Seat #" << num << " - "
                      << (seat->getStatus() == SeatStatus::Booked ? "BOOKED" : "AVAILABLE") << "\n";
        });
    std::cout << "================================================\n";
}

AVLTree<Coach::CoachID, Coach*>* CoachService::getCoachRegistry() const
{
    return coachRegistry;
}

void CoachService::saveData(const std::string& filename) const
{
    CoachRepository::saveToFile(filename, coachRegistry);
}

void CoachService::loadData(const std::string& filename)
{
    CoachRepository::loadFromFile(filename, coachRegistry);
}

void CoachService::exportStructuralData(const std::string& filename) const
{
    if (coachRegistry)
    {
        coachRegistry->exportToVisualFile(filename);
    }
}
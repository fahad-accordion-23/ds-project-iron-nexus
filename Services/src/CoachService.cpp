#include "../CoachService.hpp"
#include <iostream>

    CoachService::CoachService(TrainService* ts)
    : trainService(ts)
{
    coachRegistry = new AVLTree<Coach::CoachID, Coach*>();
}

CoachService::~CoachService()
{
    coachRegistry->traverseInOrder([](Coach::CoachID, Coach* coach) { delete coach; });
    delete coachRegistry;
}

void CoachService::addCoach(Train::TrainID trainId, const std::string& coachName, int capacity,
                            int index)
{
    Train* train = trainService->findTrain(trainId);
    if (!train)
    {
        std::cout << "[CoachService] Error: Train ID " << trainId << " not found.\n";
        return;
    }

    Coach* coach = Coach::Register(coachName, capacity);
    coachRegistry->insert(coach->getId(), coach);

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

    std::cout << "[CoachService] Coach '" << coachName << "' (ID: " << coach->getId()
              << ", Capacity: " << capacity << ") added to Train " << trainId << "\n";
}

void CoachService::removeCoach(Train::TrainID trainId, Coach::CoachID coachId)
{
    Train* train = trainService->findTrain(trainId);
    if (!train)
    {
        std::cout << "[CoachService] Error: Train ID " << trainId << " not found.\n";
        return;
    }

    // Find the coach position in the train's list
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
        coachRegistry->remove(coachId);
        std::cout << "[CoachService] Coach '" << removed->getName() << "' removed from Train "
                  << trainId << "\n";
    }
}

void CoachService::reverseTrain(Train::TrainID trainId)
{
    Train* train = trainService->findTrain(trainId);
    if (!train)
    {
        std::cout << "[CoachService] Error: Train ID " << trainId << " not found.\n";
        return;
    }

    train->reverseOrientation();
    std::cout << "[CoachService] Train " << trainId << " orientation reversed.\n";
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

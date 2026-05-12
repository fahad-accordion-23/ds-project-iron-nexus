#ifndef COACH_SERVICE_HPP
#define COACH_SERVICE_HPP

#include <string>

#include "../Structures/AVLTree.hpp"
#include "../Train/Coach.hpp"
#include "../Train/Seat.hpp"
#include "../Train/Train.hpp"

class TrainService;  // Forward declaration

/**
 * @brief Application service for managing Train Composition (Module 2) and Seating (Module 4).
 * This service is responsible for the creation, deletion, and lifecycle of all coaches.
 */
#include "TrainService.hpp"

class CoachService
{
private:
    // Global registry for all coaches across all trains.
    AVLTree<Coach::CoachID, Coach*>* coachRegistry;
    TrainService* trainService;

public:
    CoachService(TrainService* ts);
    ~CoachService();

    /**
     * @brief Add a new coach to a train. Integrates with Train's global seat pool.
     */
    void addCoach(Train::TrainID trainId, const std::string& coachName, int capacity,
                  int index = -1);

    /**
     * @brief Remove a coach. Prunes the Train's global logical seat size.
     */
    void removeCoach(Train::TrainID trainId, Coach::CoachID coachId);

    /**
     * @brief Reverse a train's orientation.
     */
    void reverseTrain(Train::TrainID trainId);

    /**
     * @brief Centralized seat booking via the Train's repositories.
     */
    bool bookSeat(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber);
    bool cancelBooking(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber);

    /**
     * @brief Inquire about seat status (Module 4).
     */
    SeatStatus checkSeatStatus(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber) const;

    /**
     * @brief Display the ordered seating chart for a specific train.
     */
    void viewSeatingChart(Train::TrainID trainId) const;

    /**
     * @brief Persistence delegation
     */
    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);
};

#endif  // COACH_SERVICE_HPP

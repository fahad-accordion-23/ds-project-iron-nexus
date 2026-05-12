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
     * @brief Create a standalone coach.
     */
    Coach::CoachID createCoach(const std::string& coachName, int capacity);

    /**
     * @brief Rehydrate a deleted coach for Undo/Redo.
     */
    void rehydrateCoach(Coach::CoachID id, const std::string& name, int capacity);

    /**
     * @brief Permanently delete a coach from the registry.
     */
    void deleteCoach(Coach::CoachID coachId);

    /**
     * @brief Link an existing coach to a train. Integrates with Train's global seat pool.
     */
    void linkCoach(Coach::CoachID coachId, Train::TrainID trainId, int index = -1);

    /**
     * @brief Unlink a coach from a train. Prunes the Train's global logical seat size.
     */
    void unlinkCoach(Coach::CoachID coachId, Train::TrainID trainId);

    /**
     * @brief View all coaches in the system.
     */
    void listAllCoaches() const;

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

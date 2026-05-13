#ifndef COACH_SERVICE_HPP
#define COACH_SERVICE_HPP

#include <string>

#include "../Structures/AVLTree.hpp"
#include "../Train/Coach.hpp"
#include "../Train/Seat.hpp"
#include "../Train/Train.hpp"

class TrainService;

#include "TrainService.hpp"

class CoachService
{
private:
    AVLTree<Coach::CoachID, Coach*>* coachRegistry;
    TrainService* trainService;

public:
    CoachService(TrainService* ts);
    ~CoachService();

    Coach::CoachID createCoach(const std::string& coachName, int capacity);

    void rehydrateCoach(Coach::CoachID id, const std::string& name, int capacity);

    void deleteCoach(Coach::CoachID coachId);

    void linkCoach(Coach::CoachID coachId, Train::TrainID trainId, int index = -1);

    void unlinkCoach(Coach::CoachID coachId, Train::TrainID trainId);

    void listAllCoaches() const;

    void reverseTrain(Train::TrainID trainId);

    void traverseTrain(Train::TrainID trainId) const;

    bool bookSeat(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber);
    bool cancelBooking(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber);

    SeatStatus checkSeatStatus(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber) const;

    void viewSeatingChart(Train::TrainID trainId) const;

    AVLTree<Coach::CoachID, Coach*>* getCoachRegistry() const;

    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);
};

#endif

#include "../CoachService.hpp"

CoachService::CoachService() : coachRegistry(nullptr) {}
CoachService::~CoachService() {}
void CoachService::addCoach(Train::TrainID trainId, const std::string& coachName, int capacity, int index) {}
void CoachService::removeCoach(Train::TrainID trainId, Coach::CoachID coachId) {}
void CoachService::reverseTrain(Train::TrainID trainId) {}
bool CoachService::bookSeat(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber) { return false; }
bool CoachService::cancelBooking(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber) { return false; }
SeatStatus CoachService::checkSeatStatus(Train::TrainID trainId, Seat::GlobalSeatNumber seatNumber) const { return SeatStatus::Available; }
void CoachService::viewSeatingChart(Train::TrainID trainId) const {}

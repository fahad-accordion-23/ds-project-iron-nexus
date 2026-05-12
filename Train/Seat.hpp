#ifndef SEAT_HPP
#define SEAT_HPP

enum class SeatStatus
{
    Available,
    Booked,
    Reserved,
    UnderMaintenance
};

class Seat
{
public:
    using GlobalSeatNumber = int;

private:
    GlobalSeatNumber number;
    SeatStatus status;

public:
    Seat(GlobalSeatNumber seatNumber, SeatStatus initialStatus = SeatStatus::Available);

    GlobalSeatNumber getNumber() const;

    SeatStatus getStatus() const;

    void setNumber(GlobalSeatNumber newNumber);

    void setStatus(SeatStatus newStatus);
};

#endif

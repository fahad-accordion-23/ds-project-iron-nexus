#include "../Seat.hpp"

Seat::Seat(GlobalSeatNumber seatNumber, SeatStatus initialStatus)
    : number(seatNumber), status(initialStatus)
{
}

Seat::GlobalSeatNumber Seat::getNumber() const
{
    return number;
}

SeatStatus Seat::getStatus() const
{
    return status;
}

void Seat::setNumber(GlobalSeatNumber newNumber)
{
    number = newNumber;
}

void Seat::setStatus(SeatStatus newStatus)
{
    status = newStatus;
}

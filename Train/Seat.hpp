#ifndef SEAT_HPP
#define SEAT_HPP

/**
 * @brief Represents the status of a single seat.
 */
enum class SeatStatus
{
    Available,
    Booked,
    Reserved,
    UnderMaintenance
};

/**
 * @brief Represents a single seat in a coach.
 *
 * In the Iron Nexus system, seats are numbered continuously across the whole train.
 * This class serves as a value type for seat data.
 */
class Seat
{
public:
    using GlobalSeatNumber = int;

private:
    GlobalSeatNumber number;
    SeatStatus status;

public:
    /**
     * @brief Construct a new Seat object.
     * @param seatNumber The unique number of the seat across the train.
     * @param initialStatus The initial booking status.
     */
    Seat(GlobalSeatNumber seatNumber, SeatStatus initialStatus = SeatStatus::Available);

    /**
     * @brief Get the seat number.
     */
    GlobalSeatNumber getNumber() const;

    /**
     * @brief Get the current status of the seat.
     */
    SeatStatus getStatus() const;

    /**
     * @brief Update the seat number (used during train renumbering).
     */
    void setNumber(GlobalSeatNumber newNumber);

    /**
     * @brief Update the status of the seat (e.g., booking or cancellation).
     */
    void setStatus(SeatStatus newStatus);
};

#endif  // SEAT_HPP

# Train
- id : const TrainID
- name : String
- coaches : List of Coaches
- 

# Coach
- id : const CoachID
- name : String
- capacity : int

# Seat
- number : int
- status : SeatStatus

--------------------------------------------------

# Station
- id : const StationID
- name : String


# Track
- id : const TrackID
- firstStation : StationID
- secondStation : StationID   
- distance
- time
- status
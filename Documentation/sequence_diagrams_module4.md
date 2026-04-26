# Module 4: Sequence Diagrams (Seating Chart)

This document provides sequence diagrams using the exact C++ signatures from the `CoachService` and `Train` skeletons.

---

## 1. Book Seat (FR-4.5)
```mermaid
sequenceDiagram
    participant Operator
    participant CS as CoachService
    participant TS as TrainService
    participant T as Train
    participant HT as HashTable

    Operator->>CS: bookSeat(trainId, seatNumber)
    CS->>TS: findTrain(trainId)
    TS-->>CS: Train*
    CS->>T: bookSeat(seatNumber)
    T->>T: findSeat(seatNumber)
    T->>HT: search(seatNumber)
    HT-->>T: Seat*
    alt seatNumber <= currentSeatSize
        T->>T: Seat->setStatus(Booked)
        T-->>CS: true
        CS-->>Operator: confirmation
    else
        T-->>CS: false
    end
```

---

## 2. Check Seat Status / Inquiry (FR-4.2, FR-4.6)
```mermaid
sequenceDiagram
    participant Traveler
    participant CS as CoachService
    participant TS as TrainService
    participant T as Train

    Traveler->>CS: checkSeatStatus(trainId, seatNumber)
    CS->>TS: findTrain(trainId)
    TS-->>CS: Train*
    CS->>T: findSeat(seatNumber)
    T-->>CS: Seat*
    CS-->>Traveler: status
```

---

## 3. View Ordered Seating Chart (FR-4.4)
```mermaid
sequenceDiagram
    participant Staff
    participant CS as CoachService
    participant TS as TrainService
    participant T as Train
    participant BST as BST

    Staff->>CS: viewSeatingChart(trainId)
    CS->>TS: findTrain(trainId)
    TS-->>CS: Train*
    CS->>T: getSeatingChart()
    T-->>CS: BST<GlobalSeatNumber, Seat*>*
    CS->>BST: inOrderTraversal()
    loop Up to currentSeatSize
        BST-->>CS: visit(Seat*)
    end
```

---

## 4. Cancel Seat Booking (FR-4.5)
```mermaid
sequenceDiagram
    participant Operator
    participant CS as CoachService
    participant TS as TrainService
    participant T as Train

    Operator->>CS: cancelBooking(trainId, seatNumber)
    CS->>TS: findTrain(trainId)
    TS-->>CS: Train*
    CS->>T: releaseSeat(seatNumber)
    T-->>CS: true
    CS-->>Operator: success
```

# Module 2: Sequence Diagrams (Coach Management)

This document provides sequence diagrams using the exact C++ signatures from the `CoachService` and `Train` skeletons.

---

## 1. Add Coach to Train (FR-2.1)
```mermaid
sequenceDiagram
    participant Operator
    participant CS as CoachService
    participant TS as TrainService
    participant T as Train
    participant C as Coach

    Operator->>CS: addCoach(trainId, coachName, capacity, index)
    CS->>TS: findTrain(trainId)
    TS-->>CS: Train*
    CS->>C: Register(coachName, capacity)
    C-->>CS: Coach*
    
    alt index == 0
        CS->>T: addCoachFront(Coach*)
    else index == -1
        CS->>T: addCoachEnd(Coach*)
    else
        CS->>T: insertCoach(Coach*, index)
    end
    
    Note over T: currentSeatSize += N
```

---

## 2. Remove Coach for Maintenance (FR-2.2)
```mermaid
sequenceDiagram
    participant Operator
    participant CS as CoachService
    participant TS as TrainService
    participant T as Train
    participant CLL as CoachList

    Operator->>CS: removeCoach(trainId, coachId)
    CS->>TS: findTrain(trainId)
    TS-->>CS: Train*
    
    CS->>T: removeCoach(position)
    T->>CLL: removeAt(position)
    
    Note over T: currentSeatSize -= capacity
    CS-->>Operator: coach uncoupled
```

---

## 3. Reverse Train Orientation (FR-2.4)
```mermaid
sequenceDiagram
    participant Operator
    participant CS as CoachService
    participant TS as TrainService
    participant T as Train

    Operator->>CS: reverseTrain(trainId)
    CS->>TS: findTrain(trainId)
    TS-->>CS: Train*
    CS->>T: reverseOrientation()
    T->>T: toggle isReversed
    CS-->>Operator: orientation reversed
```

---

## 4. Traverse Train / Engineer Walkthrough (FR-2.3)
```mermaid
sequenceDiagram
    participant Engineer
    participant T as Train
    participant CLL as CoachList

    Engineer->>T: getCoaches()
    T-->>Engineer: CircularDoublyLinkedList<Coach>*
    loop Walkthrough
        Engineer->>CLL: getNext() / getPrev()
    end
```

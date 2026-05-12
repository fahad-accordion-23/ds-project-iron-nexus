# Scheduling Service: Sequence Diagrams

This document provides sequence diagrams for assigning trains to routes, linking Module 1 (Trains) and Module 3 (Network).

---

## 1. Assign Train to Route
Assigns a specific train to a path calculated between two stations.

```mermaid
sequenceDiagram
    participant Operator
    participant SS as SchedulingService
    participant TS as TrainService
    participant NS as NetworkService
    participant HT as HashTable (Schedule)

    Operator->>SS: assignRoute(trainId, startId, endId)
    SS->>TS: findTrain(trainId)
    TS-->>SS: Train*
    alt Train Exists
        SS->>NS: suggestRoute(startId, endId)
        NS-->>SS: Optimal Route Data
        SS->>HT: insert(trainId, endId)
        SS-->>Operator: Assignment Successful
    else Train Not Found
        SS-->>Operator: Error (Invalid Train)
    end
```

---

## 2. Decommission Train Route
Removes a train from its active assignment.

```mermaid
sequenceDiagram
    participant Operator
    participant SS as SchedulingService
    participant HT as HashTable (Schedule)

    Operator->>SS: decommissionRoute(trainId)
    SS->>HT: remove(trainId)
    SS-->>Operator: Route cleared
```

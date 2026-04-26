# Module 1: Sequence Diagrams (Train Registry)

This document provides sequence diagrams using the exact C++ signatures from the `TrainService` and `Train` skeletons.

---

## 1. Register a New Train (FR-1.3)
```mermaid
sequenceDiagram
    participant Operator
    participant TS as TrainService
    participant T as Train
    participant AVL as AVLTree

    Operator->>TS: registerTrain(name)
    TS->>T: Register(name)
    T-->>TS: Train* Object
    TS->>AVL: insert(TrainID, Train*)
    AVL-->>TS: success
    TS-->>Operator: confirmation
```

---

## 2. Find Train / Emergency Stop (FR-1.2)
```mermaid
sequenceDiagram
    participant Operator
    participant TS as TrainService
    participant AVL as AVLTree
    participant T as Train

    Operator->>TS: emergencyStop(id)
    TS->>TS: findTrain(id)
    TS->>AVL: search(id)
    AVL-->>TS: Train*
    alt Train* != nullptr
        TS->>T: issueStop()
        TS-->>Operator: success
    else 
        TS-->>Operator: error
    end
```

---

## 3. Remove a Train (FR-1.3)
```mermaid
sequenceDiagram
    participant Operator
    participant TS as TrainService
    participant AVL as AVLTree

    Operator->>TS: removeTrain(id)
    TS->>AVL: remove(id)
    AVL-->>TS: success
    TS-->>Operator: decommissioned
```

---

## 4. List All Trains / Fleet Patrol (FR-1.4)
```mermaid
sequenceDiagram
    participant Operator
    participant TS as TrainService
    participant AVL as AVLTree

    Operator->>TS: listAllTrains()
    TS->>AVL: traverseInOrder()
    loop For each node
        AVL-->>TS: visit(Train*)
        TS->>TS: printDetails
    end
    TS-->>Operator: full fleet list
```

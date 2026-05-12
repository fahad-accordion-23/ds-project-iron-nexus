# Module 3: Sequence Diagrams (Railway Network)

This document provides sequence diagrams for the core functional requirements of the Railway Network module, based on the `NetworkService` and `RailwayNetwork` signatures.

---

## 1. Create a New Station
Operators can expand the network by adding up to 15 major hubs.

```mermaid
sequenceDiagram
    participant Operator
    participant NS as NetworkService
    participant S as Station
    participant AVL as AVLTree (StationRegistry)
    participant RN as RailwayNetwork
    participant G as Graph

    Operator->>NS: createStation(name)
    NS->>S: Register(name)
    S-->>NS: Station* (with auto-ID)
    NS->>AVL: insert(StationID, Station*)
    NS->>RN: addStation(Station*)
    RN->>G: addNode(Station*)
    NS-->>Operator: confirmation (StationID)
```

---

## 2. Delete a Station
Decommissioning a station involves removing it from the registry and pruning all connected tracks.

```mermaid
sequenceDiagram
    participant Operator
    participant NS as NetworkService
    participant AVL as AVLTree (StationRegistry)
    participant RN as RailwayNetwork
    participant G as Graph

    Operator->>NS: deleteStation(id)
    NS->>AVL: search(id)
    AVL-->>NS: Station*
    alt Station Found
        NS->>RN: removeStation(id)
        RN->>G: removeNode(id)
        NS->>AVL: remove(id)
        NS-->>Operator: station deleted
    else Not Found
        NS-->>Operator: error (Invalid ID)
    end
```

---

## 3. Link Two Stations (Add Track)
Establishing a connection between two hubs with a distance metric.

```mermaid
sequenceDiagram
    participant Operator
    participant NS as NetworkService
    participant RN as RailwayNetwork
    participant G as Graph

    Operator->>NS: linkStations(startId, endId, distance)
    NS->>RN: connectStations(startId, endId, distance)
    RN->>G: addEdge(startId, endId, distance)
    NS-->>Operator: track established
```

---

## 4. Suggest Optimal Route (Dijkstra)
Calculating the most efficient path by shortest distance.

```mermaid
sequenceDiagram
    participant Planner
    participant NS as NetworkService
    participant RN as RailwayNetwork
    participant G as Graph

    Planner->>NS: suggestRoute(startId, endId)
    NS->>RN: findOptimalRoute(startId, endId)
    RN->>G: findShortestPath(startId, endId)
    Note over G: Dijkstra's Algorithm execution
    G-->>RN: Path Result
    RN-->>NS: Formatted Route
    NS-->>Planner: Optimal Path Details
```

---

## 5. Show Network Map
Displaying the current connectivity of the railway system.

```mermaid
sequenceDiagram
    participant Operator
    participant NS as NetworkService
    participant RN as RailwayNetwork
    participant G as Graph

    Operator->>NS: showNetwork()
    NS->>RN: displayMap()
    RN->>G: displayGraph()
    G-->>Operator: Console output (Map)
```

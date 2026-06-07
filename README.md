# Iron Nexus 🚂

Iron Nexus is a terminal-based Railway Management System written in C++17. It is designed around custom-built data structures to handle operations like train registry, passenger seating, route calculation, and system state management. 

## Prerequisites

* **Compiler:** `g++` (or any C++17 compatible compiler)
* **Build Tool:** `make`

## Build and Run

This project includes a `Makefile` for easy compilation.

1. **Build the project:**
```bash
   make
```

2. **Run the application:**
```bash
./build/iron-nexus
```

3. **Clean build artifacts:**
```bash
make clean
```

## Directory Structure

* **`Documentation/`**: Sequence diagrams mapping out the logic for each module.
* **`Operations/`**: System logging logic.
* **`Railway/`**: Network and Station domain models.
* **`Repositories/`**: Handles reading/writing the system state to data files.
* **`Services/`**: The core business logic connecting domain models to data structures.
* **`Structures/`**: Implementation of all custom data structures (AVL, BST, Graph, Hash Table, Stack, LinkedList).
* **`Train/`**: Train, Coach, and Seat domain models.
* **`UI/`**: ANSI-colored terminal user interface.

## Usage

Once running, the application presents a numbered terminal UI. Simply type the number corresponding to the module you want to interact with and press `Enter`.

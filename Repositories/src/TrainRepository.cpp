#include "../TrainRepository.hpp"

TrainRepository::TrainRepository() : storage(nullptr) {}
TrainRepository::~TrainRepository() {}
void TrainRepository::add(Train* train) {}
void TrainRepository::remove(Train::TrainID id) {}
Train* TrainRepository::find(Train::TrainID id) const { return nullptr; }
void TrainRepository::getAll(void (*callback)(Train::TrainID, Train*)) const {}
int TrainRepository::getCount() const { return 0; }

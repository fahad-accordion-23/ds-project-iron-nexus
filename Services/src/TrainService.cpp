#include "../TrainService.hpp"

TrainService::TrainService() : trainRegistry(nullptr) {}
TrainService::~TrainService() {}
void TrainService::registerTrain(const std::string& name) {}
void TrainService::removeTrain(Train::TrainID id) {}
Train* TrainService::findTrain(Train::TrainID id) { return nullptr; }
void TrainService::listAllTrains() const {}
void TrainService::emergencyStop(Train::TrainID id) {}

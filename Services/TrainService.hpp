#ifndef TRAIN_SERVICE_HPP
#define TRAIN_SERVICE_HPP

#include <string>

#include "../Structures/AVLTree.hpp"
#include "../Train/Train.hpp"

class TrainService
{
private:
    AVLTree<Train::TrainID, Train*>* trainRegistry;

public:
    TrainService();
    ~TrainService();

    Train::TrainID registerTrain(const std::string& name);

    void removeTrain(Train::TrainID id);

    void rehydrateTrain(Train::TrainID id, const std::string& name);

    Train* findTrain(Train::TrainID id);

    void listAllTrains() const;

    void emergencyStop(Train::TrainID id);

    template <typename Func>
    void forEachTrain(Func callback) const;

    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename,
                  AVLTree<Coach::CoachID, Coach*>* coachRegistry = nullptr);
};

template <typename Func>
void TrainService::forEachTrain(Func callback) const
{
    if (trainRegistry) trainRegistry->traverseInOrder(callback);
}

#endif

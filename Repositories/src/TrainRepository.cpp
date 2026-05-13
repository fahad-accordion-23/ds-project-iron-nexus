#include "../TrainRepository.hpp"

#include <fstream>
#include <sstream>

void TrainRepository::saveToFile(const std::string& filename,
                                 const AVLTree<Train::TrainID, Train*>* storage)
{
    if (!storage) return;

    std::ofstream file(filename);
    if (!file.is_open()) return;

    storage->traverseInOrder(
        [&file](Train::TrainID id, Train* train)
        {
            // 1. Save Train Base
            file << "TRAIN," << id << "," << train->getName() << "\n";

            // 2. Save Linkages (Which coaches are on this train)
            auto coaches = train->getCoaches();
            if (coaches && !coaches->isEmpty())
            {
                for (int i = 0; i < coaches->size(); i++)
                {
                    file << "LINK," << id << "," << coaches->getAt(i)->getId() << "\n";
                }
            }

            // 3. Save Booked Seats
            auto chart = train->getSeatingChart();
            if (chart)
            {
                chart->traverseInOrder(
                    [&file, id](Seat::GlobalSeatNumber sNum, Seat* seat)
                    {
                        if (seat->getStatus() == SeatStatus::Booked)
                        {
                            file << "BOOKING," << id << "," << sNum << "\n";
                        }
                    });
            }
        });

    file.close();
}

void TrainRepository::loadFromFile(const std::string& filename,
                                   AVLTree<Train::TrainID, Train*>* storage,
                                   AVLTree<Coach::CoachID, Coach*>* coachStorage)
{
    if (!storage) return;
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        std::getline(ss, type, ',');

        if (type == "TRAIN")
        {
            std::string idStr, name;
            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            int id = std::stoi(idStr);

            Train* train = Train::Rehydrate(id, name);
            storage->insert(id, train);
        }
        else if (type == "LINK")
        {
            std::string tIdStr, cIdStr;
            std::getline(ss, tIdStr, ',');
            std::getline(ss, cIdStr, ',');

            int tId = std::stoi(tIdStr);
            int cId = std::stoi(cIdStr);

            try
            {
                // Find both objects in their respective storage trees
                Train* train = storage->search(tId);
                Coach* coach = coachStorage->search(cId);

                // Link them!
                train->addCoachEnd(coach);
                coach->setIsAttached(true);  // From the dangling pointer fix earlier
            }
            catch (...)
            {
                // Failsafe in case a coach ID doesn't exist
            }
        }
        else if (type == "BOOKING")
        {
            std::string tIdStr, sNumStr;
            std::getline(ss, tIdStr, ',');
            std::getline(ss, sNumStr, ',');

            try
            {
                Train* train = storage->search(std::stoi(tIdStr));
                train->bookSeat(std::stoi(sNumStr));
            }
            catch (...)
            {
            }
        }
    }
    file.close();
}
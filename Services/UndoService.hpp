#ifndef UNDO_SERVICE_HPP
#define UNDO_SERVICE_HPP

#include <string>

#include "../Services/CoachService.hpp"
#include "../Services/LoggerService.hpp"  // <-- Logger Included
#include "../Services/NetworkService.hpp"
#include "../Services/SchedulingService.hpp"
#include "../Services/TrainService.hpp"
#include "../Structures/CircularDoublyLinkedList.hpp"
#include "../Structures/Stack.hpp"

enum class ActionType
{
    REGISTER_TRAIN,
    REMOVE_TRAIN,
    CREATE_COACH,
    DELETE_COACH,
    LINK_COACH,
    UNLINK_COACH,
    REVERSE_TRAIN,
    CREATE_STATION,
    DELETE_STATION,
    LINK_STATIONS,
    UNLINK_STATIONS,
    BOOK_SEAT,
    CANCEL_SEAT,
    ASSIGN_ROUTE
};

struct UndoAction
{
    ActionType type;
    int primaryId;
    int secondaryId;
    std::string stringData;
    int intData;
    int intData2;

    CircularDoublyLinkedList<int>* savedCoachIds = nullptr;
    CircularDoublyLinkedList<int>* savedBookedSeats = nullptr;

    ~UndoAction()
    {
        if (savedCoachIds) delete savedCoachIds;
        if (savedBookedSeats) delete savedBookedSeats;
    }
};

class UndoService
{
private:
    Stack<UndoAction*> undoStack;
    Stack<UndoAction*> redoStack;
    TrainService* trainService;
    CoachService* coachService;
    NetworkService* networkService;
    SchedulingService* schedulingService;
    LoggerService* loggerService;  // <-- Logger Variable

    bool isUndoingRedoing;

    void executeAction(UndoAction* action, bool isUndo);
    std::string getActionName(ActionType type) const;  // <-- New Helper

public:
    UndoService(TrainService* ts, CoachService* cs, NetworkService* ns, SchedulingService* ss,
                LoggerService* ls);
    ~UndoService();

    void recordAction(ActionType type, int primaryId, int secondaryId = -1,
                      const std::string& stringData = "", int intData = -1, int intData2 = -1);

    void undo();
    void redo();

    bool isActive() const
    {
        return isUndoingRedoing;
    }
};

#endif
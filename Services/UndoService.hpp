#ifndef UNDO_SERVICE_HPP
#define UNDO_SERVICE_HPP

#include <string>

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
};

class TrainService;
class CoachService;
class NetworkService;
class SchedulingService;

class UndoService
{
private:
    Stack<UndoAction*> undoStack;
    Stack<UndoAction*> redoStack;
    TrainService* trainService;
    CoachService* coachService;
    NetworkService* networkService;
    SchedulingService* schedulingService;

    bool isUndoingRedoing;

    void executeAction(UndoAction* action, bool isUndo);

public:
    UndoService(TrainService* ts, CoachService* cs, NetworkService* ns, SchedulingService* ss);
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

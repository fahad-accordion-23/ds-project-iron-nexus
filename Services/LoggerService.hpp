#ifndef LOGGER_SERVICE_HPP
#define LOGGER_SERVICE_HPP

#include "../Operations/LogEntry.hpp"
#include "../Structures/Stack.hpp"

class LoggerService
{
private:
    Stack<LogEntry*>* history;

public:
    LoggerService();
    ~LoggerService();

    void logAction(const std::string& action, const std::string& metadata = "");

    void showRecentLogs(int count = 10);

    void clearLogs();

    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);
};

#endif

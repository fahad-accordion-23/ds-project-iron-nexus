#ifndef LOGGER_SERVICE_HPP
#define LOGGER_SERVICE_HPP

#include "../Operations/LogEntry.hpp"
#include "../Structures/Stack.hpp"

/**
 * @brief Application service for managing operation logs (Module 5).
 * Uses a Stack to ensure recent actions are reviewed first.
 */
class LoggerService
{
private:
    Stack<LogEntry*>* history;

public:
    LoggerService();
    ~LoggerService();

    /**
     * @brief Record a new operation in the system log.
     */
    void logAction(const std::string& action, const std::string& metadata = "");

    /**
     * @brief Display the most recent actions.
     * @param count Number of recent logs to show.
     */
    void showRecentLogs(int count = 10);

    /**
     * @brief Clear the operation history.
     */
    void clearLogs();
};

#endif // LOGGER_SERVICE_HPP

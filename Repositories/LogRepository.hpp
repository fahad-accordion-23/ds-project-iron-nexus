#ifndef LOG_REPOSITORY_HPP
#define LOG_REPOSITORY_HPP

#include "../Operations/LogEntry.hpp"
#include "../Structures/Stack.hpp"

/**
 * @brief Data Access Layer for managing system operation logs.
 */
class LogRepository
{
private:
    Stack<LogEntry*>* storage;

public:
    LogRepository();
    ~LogRepository();

    void push(LogEntry* entry);
    LogEntry* pop();
    LogEntry* peek() const;
    
    bool isEmpty() const;
    void clear();
};

#endif // LOG_REPOSITORY_HPP

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

    /**
     * @brief Save log history to a file.
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Load log history from a file.
     */
    void loadFromFile(const std::string& filename);
};

#endif // LOG_REPOSITORY_HPP

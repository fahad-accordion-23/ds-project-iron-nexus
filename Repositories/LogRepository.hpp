#ifndef LOG_REPOSITORY_HPP
#define LOG_REPOSITORY_HPP

#include <string>

#include "../Operations/LogEntry.hpp"
#include "../Structures/Stack.hpp"

class LogRepository
{
public:
    static void saveToFile(const std::string& filename, const Stack<LogEntry*>* storage);
    static void loadFromFile(const std::string& filename, Stack<LogEntry*>* storage);
};

#endif

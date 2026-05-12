#include "../LoggerService.hpp"
#include <iostream>

LoggerService::LoggerService() : history(nullptr)
{
    // history = new Stack<LogEntry*>();
}

LoggerService::~LoggerService()
{
    // delete history;
}

void LoggerService::logAction(const std::string& action, const std::string& metadata)
{
    // LogEntry* entry = new LogEntry(action, metadata);
    // history->push(entry);
}

void LoggerService::showRecentLogs(int count)
{
    std::cout << "\n--- Recent Operation Logs ---\n";
    // Logic: Pop from history into a temporary stack to display, then push back.
    // Or just traverse if the Stack implementation allows.
}

void LoggerService::clearLogs()
{
    // history->clear();
}

#include "../LoggerService.hpp"

#include <iostream>

LoggerService::LoggerService()
{
    history = new Stack<LogEntry*>();
}

LoggerService::~LoggerService()
{
    clearLogs();
    delete history;
}

void LoggerService::logAction(const std::string& action, const std::string& metadata)
{
    LogEntry* entry = new LogEntry(action, metadata);
    history->push(entry);
}

void LoggerService::showRecentLogs(int count)
{
    std::cout << "\n--- Recent Operation Logs ---\n";

    if (history->isEmpty())
    {
        std::cout << "  (No logs recorded)\n";
        std::cout << "----------------------------\n";
        return;
    }

    // Pop entries into a temp stack, display them, then push back
    Stack<LogEntry*> temp;
    int displayed = 0;

    while (!history->isEmpty() && displayed < count)
    {
        LogEntry* entry = history->pop();
        std::cout << "  " << entry->toString() << "\n";
        temp.push(entry);
        displayed++;
    }

    // Restore entries back to history
    while (!temp.isEmpty())
    {
        history->push(temp.pop());
    }

    std::cout << "  (" << displayed << " log(s) shown)\n";
    std::cout << "----------------------------\n";
}

void LoggerService::clearLogs()
{
    while (!history->isEmpty())
    {
        LogEntry* entry = history->pop();
        delete entry;
    }
}

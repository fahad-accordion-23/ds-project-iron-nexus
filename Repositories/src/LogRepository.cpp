#include "../LogRepository.hpp"
#include <fstream>
#include <iostream>

LogRepository::LogRepository()
{
    storage = new Stack<LogEntry*>();
}

LogRepository::~LogRepository()
{
    clear();
    delete storage;
}

void LogRepository::push(LogEntry* entry)
{
    storage->push(entry);
}

LogEntry* LogRepository::pop()
{
    if (storage->isEmpty()) return nullptr;
    return storage->pop();
}

LogEntry* LogRepository::peek() const
{
    if (storage->isEmpty()) return nullptr;
    return storage->peek();
}

bool LogRepository::isEmpty() const
{
    return storage->isEmpty();
}

void LogRepository::clear()
{
    while (!storage->isEmpty())
    {
        LogEntry* entry = storage->pop();
        delete entry;
    }
}

void LogRepository::saveToFile(const std::string& filename) const
{
    // To save stack contents, we need a temporary stack to reverse the order
    Stack<LogEntry*> temp;
    Stack<LogEntry*>* source = const_cast<Stack<LogEntry*>*>(storage);
    Stack<LogEntry*> backup;

    // Move all to temp (reversed order)
    while (!source->isEmpty())
    {
        LogEntry* e = source->pop();
        temp.push(e);
    }

    std::ofstream file(filename);
    if (file.is_open())
    {
        // Write from temp (original order, oldest first)
        while (!temp.isEmpty())
        {
            LogEntry* e = temp.pop();
            file << e->getAction() << "|" << e->getTimestamp() << "|" << e->getMetadata() << "\n";
            backup.push(e); // save for restoring
        }
        file.close();
    }

    // Restore original stack
    while (!backup.isEmpty())
    {
        source->push(backup.pop());
    }
}

void LogRepository::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        size_t first = line.find('|');
        if (first == std::string::npos) continue;
        size_t second = line.find('|', first + 1);

        std::string action = line.substr(0, first);
        std::string metadata = (second != std::string::npos) ? line.substr(second + 1) : "";

        LogEntry* entry = new LogEntry(action, metadata);
        storage->push(entry);
    }

    file.close();
}

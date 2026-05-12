#include "../LogRepository.hpp"

#include <fstream>

void LogRepository::saveToFile(const std::string& filename, const Stack<LogEntry*>* storage)
{
    if (!storage) return;

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
            backup.push(e);  // save for restoring
        }
        file.close();
    }

    // Restore original stack
    while (!backup.isEmpty())
    {
        source->push(backup.pop());
    }
}

void LogRepository::loadFromFile(const std::string& filename, Stack<LogEntry*>* storage)
{
    if (!storage) return;

    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line))
    {
        size_t first = line.find('|');
        if (first == std::string::npos) continue;
        size_t second = line.find('|', first + 1);
        if (second == std::string::npos) continue;

        std::string action = line.substr(0, first);
        std::string ts = line.substr(first + 1, second - first - 1);
        std::string metadata = line.substr(second + 1);

        LogEntry* entry = new LogEntry(action, ts, metadata);
        storage->push(entry);
    }

    file.close();
}

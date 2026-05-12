#include "../LogRepository.hpp"

LogRepository::LogRepository() : storage(nullptr) {}
LogRepository::~LogRepository() {}
void LogRepository::push(LogEntry* entry) {}
LogEntry* LogRepository::pop() { return nullptr; }
LogEntry* LogRepository::peek() const { return nullptr; }
bool LogRepository::isEmpty() const { return true; }
void LogRepository::clear() {}
void LogRepository::saveToFile(const std::string& filename) const {}
void LogRepository::loadFromFile(const std::string& filename) {}

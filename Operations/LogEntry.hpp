#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP

#include <string>

class LogEntry
{
private:
    std::string action;
    std::string timestamp;
    std::string metadata;

public:
    LogEntry(const std::string& action, const std::string& metadata = "");
    LogEntry(const std::string& action, const std::string& ts, const std::string& metadata);

    std::string getAction() const;
    std::string getTimestamp() const;
    std::string getMetadata() const;

    std::string toString() const;
};

#endif

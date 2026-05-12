#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP

#include <string>

/**
 * @brief Represents a single event in the system's history.
 */
class LogEntry
{
private:
    std::string action;
    std::string timestamp;
    std::string metadata;

public:
    LogEntry(const std::string& action, const std::string& metadata = "");

    std::string getAction() const;
    std::string getTimestamp() const;
    std::string getMetadata() const;

    /**
     * @brief Formats the log entry for terminal display.
     */
    std::string toString() const;
};

#endif  // LOG_ENTRY_HPP

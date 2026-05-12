#include "../LogEntry.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>

LogEntry::LogEntry(const std::string& action, const std::string& metadata)
    : action(action), metadata(metadata)
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    timestamp = ss.str();
}

std::string LogEntry::getAction() const { return action; }
std::string LogEntry::getTimestamp() const { return timestamp; }
std::string LogEntry::getMetadata() const { return metadata; }

std::string LogEntry::toString() const
{
    return "[" + timestamp + "] " + action + (metadata.empty() ? "" : " | Data: " + metadata);
}

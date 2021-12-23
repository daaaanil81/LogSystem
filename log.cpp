#include "log.h"

ConsoleLog::ConsoleLog(std::string message, ThreadId id) {
    m_message = message;
    m_id = id;
}

std::mutex ConsoleLog::m_mutex;

std::string levelToString(LogLevel l) {
    switch (l) {
    case INFO:
        return "INFO";
    case DEBUG:
        return "DEBUG";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    default:
        return "";
    }
}

ConsoleLog::StreamControl ConsoleLog::operator()(LogLevel level) {
    return ConsoleLog::StreamControl(this->m_ss, level, this->m_message, this->m_id);
}


ConsoleLog getLogger(const std::string& str) {
    std::thread::id thread_id = std::this_thread::get_id();

    return ConsoleLog(str, thread_id);
}


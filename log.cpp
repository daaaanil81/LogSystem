#include "log.h"

/* ConsoleLog::ConsoleLog() { */
/*     std::cout << "ConsoleLog()" << std::endl; */
/* } */

/* ConsoleLog::~ConsoleLog() { */
/*     std::cout << "~ConsoleLog()" << std::endl; */
/* } */

std::mutex ConsoleLog::m_mutex;
std::map<std::thread::id, std::string> ConsoleLog::m_mapThreads;

void ConsoleLog::setMessage(std::string message, std::thread::id thread_id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_mapThreads[thread_id] = message;
}

void ConsoleLog::getMessage(std::thread::id thread_id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::cout << m_mapThreads[thread_id] << std::endl;
}

ConsoleLog& ConsoleLog::getInstance(std::string message) {
    static ConsoleLog instance;

    std::thread::id thread_id = std::this_thread::get_id();

    instance.setMessage(message, thread_id);

    return instance;
}

std::string ConsoleLog::levelToString(LogLevel l) {
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

ConsoleLog& ConsoleLog::operator()(LogLevel level) {
    std::string level_str = levelToString(level);
    std::cout << __DATE__ << " " << __TIME__ << ";" << " " << level_str << ";";
    return *this;
}

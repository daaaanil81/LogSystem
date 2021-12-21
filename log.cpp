#include "log.h"

/* ConsoleLog::ConsoleLog() { */
/*     std::cout << "ConsoleLog()" << std::endl; */
/* } */

/* ConsoleLog::~ConsoleLog() { */
/*     std::cout << "~ConsoleLog()" << std::endl; */
/* } */

void ConsoleLog::setMessage(std::string message, std::thread::id thread_id) {
    std::cout << message << ":" << thread_id << ":" << std::endl;
    m_message = message;
}

ConsoleLog& getLogger(std::string message) {
    std::thread::id this_id = std::this_thread::get_id();

    auto& log = ConsoleLog::getInstance(message, this_id);

    std::cout << "thread " << this_id << " sleeping...\n";

    return log;
}

ConsoleLog& ConsoleLog::getInstance(std::string message, std::thread::id thread_id) {
    static ConsoleLog instance;

    instance.setMessage(message, thread_id);

    return instance;
}

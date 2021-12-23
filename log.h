#ifndef _LOG__H_
#define _LOG__H_

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

/*
Example of console output:
23.02.2020 18:06:06; INFO; (1020): Starting the app
23.02.2020 18:06:06; DEBUG; (2561): Running a thread

Example of log.txt output:
23.02.2020 18:06:06; INFO; (2561): Running a thread
23.02.2020 18:06:06; DEBUG; f2(3444): Running a thread
23.02.2020 18:06:06; WARNING; f2(3444): Time spent in the thread: 10.0 seconds

Example of log2.txt:
23.02.2020 18:06:06; INFO; f3(3444): Running a thread
23.02.2020 18:06:06; ERROR; f3(3444): My int is 123;
*/

/*
void f1() {
    auto logger1 = getLogger(); // Log to console
    // output: 23.02.2020 18:06:06; DEBUG; (2561): Running a thread
    logger1(DEBUG) << "Running a thread";

    auto logger2 = getLogger("f1"); // Each message has f1 prefix
    // output: 23.02.2020 18:06:06; INFO; (2561): Running a thread
    logger2 << "Running a thread" << " but log to another logger"; // Default log level INFO
}
*/

enum LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR
};

std::string levelToString(LogLevel level);

class ConsoleLog {

    using ThreadId = std::thread::id;

private: /* Structs */
    struct StreamControl {
        std::stringstream& m_ss;

        explicit StreamControl(std::stringstream& ss, LogLevel level, const std::string& message, ThreadId id) : m_ss(ss) {
            std::string level_str = levelToString(level);

            m_ss << __DATE__ << " " << __TIME__ << ";" << " " << level_str << "; ";

            if (!message.empty()) {
                m_ss << message;
            }

            m_ss << "(" << id << "): ";
        }

        ~StreamControl() {
            std::lock_guard<std::mutex> lock(ConsoleLog::m_mutex);
            std::cout << m_ss.str() << std::endl;
            m_ss.str("");
        }
    };

private: /* Variables */
    static std::mutex m_mutex;
    std::stringstream m_ss;
    std::string m_message;
    ThreadId m_id;

private: /* Functions */
public:
    explicit ConsoleLog(std::string message, ThreadId id);

    ConsoleLog::StreamControl operator()(LogLevel level = INFO);

    template <class Type>
    ConsoleLog::StreamControl operator<<(const Type& val) {
        ConsoleLog::StreamControl sc(this->m_ss, INFO, this->m_message, this->m_id);
        sc.m_ss << val;
        return sc;
    }
};

template <class Type>
ConsoleLog::StreamControl&& operator<<(ConsoleLog::StreamControl&& sc, const Type& val) {
    sc.m_ss << val;
    return std::move(sc);
}

ConsoleLog getLogger(const std::string& str = "");

#endif /* _LOG__H_ */

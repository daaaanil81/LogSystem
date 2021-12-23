#ifndef _LOG__H_
#define _LOG__H_

#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <mutex>

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

#define getLogger(message) ConsoleLog::getInstance(message)

class ConsoleLog {
private:
    std::string m_message;
    static std::mutex m_mutex;
    static std::map<std::thread::id, std::string> m_mapThreads;
private:
    ConsoleLog() {}
    void setMessage(std::string message, std::thread::id thread_id);
    std::string levelToString(LogLevel level);
public:
    ConsoleLog& operator=(ConsoleLog&) = delete;

    void getMessage(std::thread::id thread_id);
    static ConsoleLog& getInstance(std::string message);

    ConsoleLog& operator()(LogLevel level = INFO);

    template <class Type>
    ConsoleLog& operator<<(const ConsoleLog& log, const Type& val) {

    }
};

#endif /* _LOG__H_ */

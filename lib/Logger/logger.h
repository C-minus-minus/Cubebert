#ifndef LOGGER_H
#define LOGGER_H

#include <map>
#include <string>

enum LogLevel {
    ERROR,
    WARNING,
    INFO,
    DEBUG
};

class Logger {
public:
    Logger(LogLevel level = LogLevel::INFO);

    static Logger *instance();

    Logger info();
    Logger error();
    Logger debug();
    Logger warning();

    // Logger fields(std::map<std::string, std::stri> fields);

    void message(std::string message);

private:
    LogLevel m_maxLogLevel;
    LogLevel m_logLevel;
};

#endif

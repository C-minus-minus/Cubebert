#include "logger.h"

#include <iostream>
#include <iomanip>

const std::string RED = "\033[31m";
const std::string YELLOW = "\033[33m";
// const std::string green = "\033[32m";
const std::string CYAN = "\033[36m";
const std::string RESET = "\033[0m";

Logger::Logger(LogLevel level) : m_maxLogLevel(level) {
    std::cout << std::fixed << std::setprecision(4);
}

Logger *Logger::instance() {
    static Logger instance;
    return &instance;
}

Logger Logger::info() {
    m_logLevel = INFO;
    return *this;
}

Logger Logger::error() {
    m_logLevel = ERROR;
    return *this;
}

Logger Logger::debug() {
    m_logLevel = DEBUG;
    return *this;
}

Logger Logger::warning() {
    m_logLevel = WARNING;
    return *this;
}

void Logger::message(std::string message) {
    if (m_logLevel > m_maxLogLevel) {
        return;
    }

    switch (m_logLevel) {
        case ERROR: std::cout << RED <<      "[ERROR] "; break;
        case WARNING: std::cout << YELLOW << "[WARN]  "; break;
        case INFO: std::cout <<              "[INFO]  "; break;
        case DEBUG: std::cout << CYAN <<     "[DEBUG] "; break;
    }

    std::cout << message << RESET << std::endl;
}
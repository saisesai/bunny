#include "bunny/logger.h"

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

#include <bunny/file_system.h>

bunny::Logger::~Logger() {
    mFile.close();
}

bunny::Logger &bunny::Logger::Tag(const char *tag) {
    mTag = tag;
    return *this;
}

void bunny::Logger::SetLevel(bunny::Logger::Level level) {
    mLevel = level;
}

void bunny::Logger::Debug(const char *fmt, ...) {
    va_list vaList;
    va_start(vaList, fmt);
    vPrintLn(Level::DEBUG, fmt, vaList);
    va_end(vaList);
}

void bunny::Logger::Info(const char *fmt, ...) {
    va_list vaList;
    va_start(vaList, fmt);
    vPrintLn(Level::INFO, fmt, vaList);
    va_end(vaList);
}

void bunny::Logger::Warning(const char *fmt, ...) {
    va_list vaList;
    va_start(vaList, fmt);
    vPrintLn(Level::WARNING, fmt, vaList);
    va_end(vaList);
}

void bunny::Logger::Error(const char *fmt, ...) {
    va_list vaList;
    va_start(vaList, fmt);
    vPrintLn(Level::ERROR, fmt, vaList);
    va_end(vaList);
}

void bunny::Logger::Fatal(const char *fmt, ...) {
    va_list vaList;
    va_start(vaList, fmt);
    vPrintLn(Level::FATAL, fmt, vaList);
    va_end(vaList);
}

void bunny::Logger::OpenFile() {
    std::stringstream tss;
    std::time_t ns = time(nullptr);
    std::tm *now = std::localtime(&ns);
    tss << 1900 + now->tm_year
        << "_" << now->tm_mon + 1
        << "_" << now->tm_mday << "_"
        << std::setw(2) << std::setfill('0') << now->tm_hour
        << std::setw(2) << std::setfill('0') << now->tm_min
        << std::setw(2) << std::setfill('0') << now->tm_sec << ".log";
    mFile = FileSystem::Log::Open(tss.str(), std::ios::out | std::ios::app);
    if (!mFile.is_open()) {
        Fatal("failed to create log file: %s", FileSystem::Log::AbsolutePath(tss.str()).c_str());
    }
    LOGI("log file: %s", FileSystem::Log::AbsolutePath(tss.str()).c_str());
}

bunny::Logger &bunny::Logger::GetInstance() {
    static Logger INSTANCE;
    return INSTANCE;
}

const char *bunny::Logger::GetLevelStr(bunny::Logger::Level level) {
    switch (level) {
        case Level::DEBUG:
            return "DEBUG";
        case Level::INFO:
            return "INFO";
        case Level::WARNING:
            return "WARNING";
        case Level::ERROR:
            return "ERROR";
        case Level::FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}

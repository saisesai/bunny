#ifndef bunny_LOG_H
#define bunny_LOG_H

#include <cstdarg>

#include <string>
#include <fstream>

namespace bunny {
    class Logger {
    public:
        enum class Level {
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            FATAL
        };
    public:

        void SetLevel(Level level);

        Logger& Tag(const char *tag);

        void Debug(const char *fmt, ...);

        void Info(const char *fmt, ...);

        void Warning(const char *fmt, ...);

        void Error(const char *fmt, ...);

        void Fatal(const char *fmt, ...);

        void OpenFile();

        Logger(const Logger &) = delete; // singleton

        void operator=(const Logger &) = delete; // singleton

        static Logger &GetInstance(); // singleton

        static const char *GetLevelStr(Level level);

    private:
        const char* TAG = "bunny::logger";
        std::string mTag;
        std::fstream mFile;
        Level mLevel = Level::DEBUG;

        Logger() = default;

        virtual ~Logger();

        void vPrintLn(Level level, const char *fmt, std::va_list args);
    };
}

#define LOGD(...) bunny::Logger::GetInstance().Tag(TAG).Debug(__VA_ARGS__)
#define LOGI(...) bunny::Logger::GetInstance().Tag(TAG).Info(__VA_ARGS__)
#define LOGW(...) bunny::Logger::GetInstance().Tag(TAG).Warning(__VA_ARGS__)
#define LOGE(...) bunny::Logger::GetInstance().Tag(TAG).Error(__VA_ARGS__)
#define LOGF(...) bunny::Logger::GetInstance().Tag(TAG).Fatal(__VA_ARGS__)

#define LOG_LEVEL(__level) bunny::Logger::GetInstance().SetLevel(__level)

#endif //bunny_LOG_H

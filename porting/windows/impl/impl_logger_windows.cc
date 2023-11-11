#include "bunny/logger.h"

#include <cstdio>
#include <cstdlib>

void bunny::Logger::vPrintLn(Level level, const char *fmt, std::va_list args) {
    if (level < mLevel) {
        return;
    }
    std::printf("[%s][%s] ", mTag.c_str(), GetLevelStr(level));
    char buffer[512] = {0};
    std::vsprintf(buffer, fmt, args);
    printf("%s", buffer);
    std::printf("\r\n");
    if (mFile.is_open()) {
        mFile << "[" << mTag << "][" << GetLevelStr(level) << "] " << buffer << std::endl;
    }
    mTag = TAG;
    if (level == Level::FATAL) {
        std::exit(-1);
    }
}

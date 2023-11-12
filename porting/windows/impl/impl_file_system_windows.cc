#include "bunny/file_system.h"

#include <filesystem>

namespace fs = std::filesystem;

#include "bunny/logger.h"

void bunny::FileSystem::getPath() {
    mLogPath = fs::absolute("./log").string();
    if (!exist(mLogPath)) createDirectories(mLogPath);
    LOGI("log path: %s", mLogPath.c_str());
    mDataPath = fs::absolute("./data").string();
    if (!exist(mDataPath)) createDirectories(mDataPath);
    LOGI("data path: %s", mDataPath.c_str());
    mCachePath = fs::absolute("./cache").string();
    if (!exist(mCachePath)) createDirectories(mCachePath);
    LOGI("cache path: %s", mCachePath.c_str());
    mAssetsPath = fs::absolute("./assets").string();
    if (!exist(mAssetsPath)) createDirectories(mAssetsPath);
    LOGI("assets path: %s", mAssetsPath.c_str());
}

bool bunny::FileSystem::exist(const std::string &path) {
    return fs::exists(path);
}

bool bunny::FileSystem::remove(const std::string &path) {
    return fs::remove_all(path);
}

bool bunny::FileSystem::createDirectories(const std::string &path) {
    return std::filesystem::create_directories(path);
}
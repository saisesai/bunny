#include "bunny/file_system.h"

bunny::FileSystem &bunny::FileSystem::GetInstance() {
    static FileSystem INSTANCE;
    return INSTANCE;
}

bunny::FileSystem::FileSystem() {
    this->getPath();
}

std::string bunny::FileSystem::LogPath() const {
    return mLogPath;
}

std::string bunny::FileSystem::DataPath() const {
    return mDataPath;
}

std::string bunny::FileSystem::CachePath() const {
    return mCachePath;
}

std::string bunny::FileSystem::AssetsPath() const {
    return mAssetsPath;
}

bool bunny::FileSystem::Log::Exist(const std::string &path) {
    return exist(AbsolutePath(path));
}

bool bunny::FileSystem::Log::Remove(const std::string &path) {
    return remove(AbsolutePath(path));
}

bool bunny::FileSystem::Log::CreateDirectories(const std::string &path) {
    return createDirectories(AbsolutePath(path));
}

std::fstream bunny::FileSystem::Log::Open(const std::string &path, std::ios_base::openmode mode) {
    std::fstream f;
    f.open(AbsolutePath(path).c_str(), mode);
    return f;
}

std::FILE *bunny::FileSystem::Log::OpenC(const std::string &path, const char *mode) {
    std::FILE *f = std::fopen(AbsolutePath(path).c_str(), mode);
    return f;
}

std::string bunny::FileSystem::Log::AbsolutePath(const std::string &path) {
    return std::string(GetInstance().LogPath() + "/" + path);
}

std::string bunny::FileSystem::Assets::AbsolutePath(const std::string &path) {
    return std::string(GetInstance().AssetsPath() + "/" + path);
}

bool bunny::FileSystem::Assets::Exist(const std::string &path) {
    return exist(AbsolutePath(path));
}

bool bunny::FileSystem::Assets::CreateDirectories(const std::string &path) {
    return createDirectories(AbsolutePath(path));
}

std::fstream bunny::FileSystem::Assets::Open(const std::string &path, std::ios_base::openmode mode) {
    std::fstream f;
    f.open(AbsolutePath(path).c_str(), mode);
    return f;
}

std::FILE *bunny::FileSystem::Assets::OpenC(const std::string &path, const char *mode) {
    std::FILE *f = std::fopen(AbsolutePath(path).c_str(), mode);
    return f;
}

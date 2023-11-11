#ifndef BUNNY_FILE_SYSTEM_H
#define BUNNY_FILE_SYSTEM_H

#include <cstdio>
#include <string>
#include <fstream>

namespace bunny {
    class FileSystem {
    public:
        class Log {
        public:
            static std::string AbsolutePath(const std::string &path);

            static bool Exist(const std::string &path);

            static bool Remove(const std::string &path);

            static bool CreateDirectories(const std::string &path);

            static std::fstream Open(const std::string &path, std::ios_base::openmode mode);

            static std::FILE *OpenC(const std::string &path, const char* mode);
        };

        class Data {
        public:
            static bool Exist(const std::string &path);

            static bool CreateDirectories(const std::string &path);

            static std::fstream Open(const std::string &path);

            static std::FILE *OpenC(const std::string &path);
        };

        class Cache {
            static bool Exist(const std::string &path);

            static bool CreateDirectories(const std::string &path);

            static std::fstream Open(const std::string &path);

            static std::FILE *OpenC(const std::string &path);
        };

        class Assets {
            static bool Exist(const std::string &path);

            static bool CreateDirectories(const std::string &path);

            static std::fstream Open(const std::string &path);

            static std::FILE *OpenC(const std::string &path);
        };

    public:
        FileSystem(const FileSystem &) = delete;

        void operator=(const FileSystem &) = delete;

        [[nodiscard]] std::string LogPath() const;

        [[nodiscard]] std::string DataPath() const;

        [[nodiscard]] std::string CachePath() const;

        [[nodiscard]] std::string AssetsPath() const;

        static FileSystem &GetInstance();

    private:
        const char *TAG = "bunny::filesystem";
        std::string mLogPath;
        std::string mDataPath;
        std::string mCachePath;
        std::string mAssetsPath;

        void getPath();

        FileSystem();

        virtual ~FileSystem() = default;

        static bool exist(const std::string &path);

        static bool remove(const std::string &path);

        static bool createDirectories(const std::string &path);
    };
}

#endif //BUNNY_FILE_SYSTEM_H

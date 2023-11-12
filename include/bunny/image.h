#ifndef BUNNY_APP_IMAGE_H
#define BUNNY_APP_IMAGE_H

#include <string>
#include <vector>
#include "imgui.h"
#include "GLES2/gl2.h"

extern "C" {
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}

namespace bunny {
    class Image {
    public:
        const char *TAG = "bunny::image";

        Image() = default;

        explicit Image(const std::string &path);

        virtual ~Image();

        void Load(const std::string &path);

        [[nodiscard]] bool IsLoaded() const;

        [[nodiscard]] ImTextureID GetTexture() const;

    private:
        std::string mPath;
        bool mIsLoaded = false;
        ImVec2 mSize{0, 0};
        GLuint mTexture = 0;
        AVFrame *mFrame = nullptr;
        AVPacket *mPacket = nullptr;
        AVStream *mStream = nullptr;
        std::vector<uint8_t> mBuffer;
        const AVCodec *mCodec = nullptr;
        AVCodecContext *mCodecContext = nullptr;
        AVFormatContext *mFormatContext = nullptr;

        bool mGetStream();

        bool mGetFormatContext();

        bool mGetImagePixelBuffer();

        bool mGetImageTextureFromFrame();

        void mGetRgbaDataFromFrame(AVFrame* frame);
    };
}

#endif //BUNNY_APP_IMAGE_H

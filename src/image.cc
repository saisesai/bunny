#include "bunny/image.h"

#include "bunny/logger.h"

bunny::Image::Image(const std::string &path) : Image() {
    mPath = path;
    Load(mPath);
}

bunny::Image::~Image() {
    glDeleteTextures(1, &mTexture);
}

ImTextureID bunny::Image::GetTexture() const {
    return ImTextureID(uintptr_t(mTexture));
}

bool bunny::Image::IsLoaded() const {
    return mIsLoaded;
}

void bunny::Image::Load(const std::string &path) {
    mPath = path;
    if (!mGetFormatContext()) {
        LOGE("failed to get format context for: %s", mPath.c_str());
        return;
    }
    if (!mGetStream()) {
        LOGE("failed to get codec pars for: %s", mPath.c_str());
        return;
    }
    mCodec = avcodec_find_decoder(mStream->codecpar->codec_id);
    if (mCodec == nullptr) {
        LOGE("failed to find codec for: %s", mPath.c_str());
        return;
    }
    mCodecContext = avcodec_alloc_context3(mCodec);
    if (mCodecContext == nullptr) {
        LOGE("failed to alloc codec context for: %s", mCodec->name);
        return;
    }
    if (avcodec_parameters_to_context(mCodecContext, mStream->codecpar) < 0) {
        LOGE("failed to convert codec par to context for: %s", mCodec->name);
        return;
    }
    if (avcodec_open2(mCodecContext, mCodec, nullptr) < 0) {
        LOGE("failed to open codec for: %s", mCodec->name);
        return;
    }
    mFrame = av_frame_alloc();
    if (mFrame == nullptr) {
        LOGE("failed to alloc frame for: %s", mPath.c_str());
        return;
    }
    mPacket = av_packet_alloc();
    if (mPacket == nullptr) {
        LOGE("failed to alloc packet for: %s", mPath.c_str());
        return;
    }
    if (av_read_frame(mFormatContext, mPacket) < 0) {
        LOGE("failed to read frame data for: %s", mPath.c_str());
        return;
    }
    int rc = avcodec_send_packet(mCodecContext, mPacket);
    if (rc < 0) {
        LOGE("failed to send pack to codec: %s", av_err2str(rc));
        return;
    }
    rc = avcodec_receive_frame(mCodecContext, mFrame);
    if (rc < 0) {
        LOGE("failed to receive frame from codec: %s", av_err2str(rc));
        return;
    }
    mSize.x = float(mFrame->width);
    mSize.y = float(mFrame->height);
    mBuffer.resize(int(mSize.x * mSize.y * 4));
    if (!mGetImageTextureFromFrame()) {
        LOGE("failed to get image texture from frame!");
        return;
    }
    av_packet_unref(mPacket);
    av_frame_free(&mFrame);
    av_packet_free(&mPacket);
    avcodec_close(mCodecContext);
    avformat_close_input(&mFormatContext);
    avcodec_free_context(&mCodecContext);
    avformat_free_context(mFormatContext);
    mIsLoaded = true;
}

bool bunny::Image::mGetFormatContext() {
    mFormatContext = avformat_alloc_context();
    if (mFormatContext == nullptr) {
        LOGE("failed to alloc context!");
        return false;
    }
    if (avformat_open_input(&mFormatContext, mPath.c_str(), nullptr, nullptr) != 0) {
        LOGE("failed to open input: %s", mPath.c_str());
        return false;
    }
    if (avformat_find_stream_info(mFormatContext, nullptr) < 0) {
        LOGE("failed to find stream info: %s", mPath.c_str());
        return false;
    }
    return true;
}

bool bunny::Image::mGetStream() {
    if (mFormatContext->nb_streams == 1) {
        if (mFormatContext->streams[0]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            mStream = mFormatContext->streams[0];
            return true;
        } else {
            LOGE("wrong media type: %s", av_get_media_type_string(mFormatContext->streams[0]->codecpar->codec_type));
            return false;
        }
    } else {
        LOGE("wrong stream number: [%s] != 1", mFormatContext->nb_streams);
        return false;
    }
}

bool bunny::Image::mGetImageTextureFromFrame() {
    if (!mGetImagePixelBuffer()) {
        return false;
    }
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same
    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 mFrame->width, mFrame->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mBuffer.data());
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

bool bunny::Image::mGetImagePixelBuffer() {
    if (mFrame->format == AV_PIX_FMT_RGBA) {
        mGetRgbaDataFromFrame(mFrame);
        return true;
    }
    AVFrame *dst = av_frame_alloc();
    if (dst == nullptr) {
        LOGE("failed to alloc rgba frame!");
        return false;
    }
    dst->width = mFrame->width;
    dst->height = mFrame->height;
    dst->format = AV_PIX_FMT_RGBA;
    if (av_image_alloc(dst->data, dst->linesize, dst->width, dst->height, AV_PIX_FMT_RGBA, 4) < 0) {
        LOGE("failed to alloc buffer for rgba frame!");
        return false;
    }
    SwsContext *swsContext = sws_getContext(
            mFrame->width, mFrame->height, AVPixelFormat(mFrame->format),
            dst->width, dst->height, AV_PIX_FMT_RGBA,
            SWS_FAST_BILINEAR | SWS_FULL_CHR_H_INT | SWS_ACCURATE_RND, nullptr, nullptr, nullptr);
    if (swsContext == nullptr) {
        LOGE("failed to create sws context!");
        return false;
    }
    sws_scale(swsContext, mFrame->data, mFrame->linesize,
              0, mFrame->height, dst->data, dst->linesize);
    mGetRgbaDataFromFrame(dst);

    sws_freeContext(swsContext);
    av_freep(dst->data);
    av_frame_free(&dst);
    return true;
}

void bunny::Image::mGetRgbaDataFromFrame(AVFrame* frame) {
    std::memcpy(mBuffer.data(), frame->data[0], frame->width * frame->height * 4);
}

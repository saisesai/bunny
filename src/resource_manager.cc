#include "bunny/resource_manager.h"

extern "C" {
#include "libavutil/avutil.h"
}

bunny::ResourceManger::ResourceManger() {
    av_log_set_level(AV_LOG_ERROR);
}

bunny::ResourceManger &bunny::ResourceManger::GetInstance() {
    static ResourceManger INSTANCE;
    return INSTANCE;
}

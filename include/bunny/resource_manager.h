#ifndef BUNNY_RESOURCE_MANAGER_H
#define BUNNY_RESOURCE_MANAGER_H

#include <string>

namespace bunny {
    class ResourceManger {
    public:
        const char *TAG = "bunny::resource_manager";

        ResourceManger(const ResourceManger &) = delete;

        void operator=(const ResourceManger &) = delete;

        static ResourceManger &GetInstance();

    private:

        ResourceManger();

        virtual ~ResourceManger() = default;
    };
}

#endif //BUNNY_RESOURCE_MANAGER_H

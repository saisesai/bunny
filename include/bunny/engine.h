#ifndef BUNNY_ENGINE_H
#define BUNNY_ENGINE_H

#include "bunny/image.h"
#include "bunny/logger.h"
#include "bunny/file_system.h"
#include "bunny/resource_manager.h"

namespace bunny {
    class Engine {
    public:
        Engine(const Engine &) = delete;

        void operator=(const Engine &) = delete;

        static Engine &GetInstance();

    private:
        Engine();

        virtual ~Engine() = default;
    };
}

#endif //BUNNY_ENGINE_H

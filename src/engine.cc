#include "bunny/engine.h"

bunny::Engine &bunny::Engine::GetInstance() {
    static Engine INSTANCE;
    return INSTANCE;
}

bunny::Engine::Engine() {
    LOG_LEVEL(bunny::Logger::Level::DEBUG);
    bunny::FileSystem::GetInstance();
    bunny::Logger::GetInstance().OpenFile();
    bunny::ResourceManger::GetInstance();
}

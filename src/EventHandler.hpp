#pragma once

#include <SDL3/SDL.h>

class EventHandler
{
    public:
        EventHandler() = delete;
        ~EventHandler() = delete;

        static bool sdlPollEvent();
};

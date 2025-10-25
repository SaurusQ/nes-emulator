#pragma once

#include <SDL3/SDL.h>

struct Area
{
    float x;
    float y;
    float xb;
    float yb;
};

class EventHandler
{
    public:
        EventHandler();
        ~EventHandler() = default;

        bool sdlPollEvent();
        void setMemoryScrollArea(float x, float y, float xb, float yb) { memoryScrollArea = {x, y, xb, yb}; }

        uint16_t memoryPointer = 0x0000;
    private:
        Area memoryScrollArea = {0.0f, 0.0f, 0.0f, 0.0f};
};

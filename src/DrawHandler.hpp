#pragma once

#include <SDL3/SDL.h>

class DrawHandler
{
    public:
        DrawHandler() = delete;
        ~DrawHandler() = delete;

        static void drawFrame(SDL_Renderer* renderer);
};

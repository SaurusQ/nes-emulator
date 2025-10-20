#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>

class DrawHandler
{
    public:
        DrawHandler(SDL_Renderer* renderer);
        ~DrawHandler();

        void drawFrame();
        void drawText(std::string text, int x, int y);
    
    private:
        SDL_Renderer* renderer_;
        TTF_Font* font_;
        SDL_Color fontColor_ = { 255, 255, 255, 255 };
};

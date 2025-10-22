#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <vector>

constexpr int FONT_SIZE = 24;

constexpr SDL_Color makeColor(uint32_t hexColor, uint8_t alpha = 255)
{
    return { static_cast<uint8_t>((hexColor >> 16) & 0xFFu),
             static_cast<uint8_t>((hexColor >> 8)  & 0xFFu),
             static_cast<uint8_t>((hexColor)       & 0xFFu),
             alpha };
}

class DrawHandler
{
    public:
        DrawHandler(SDL_Renderer* renderer);
        ~DrawHandler();

        void drawFrame();
        std::pair<int , int> drawText(std::string text, int x, int y, bool highlightFirst = false);
        void drawStatusRegister(uint8_t statusRegister, int x, int y);
    
    private:
        void createCharacterTextures(std::string text, SDL_Color textColor, std::vector<SDL_Texture*>& output);

        SDL_Renderer* renderer_;
        TTF_Font* font_;
        SDL_Color fontColor_                = { 255, 255, 255, 255 };
        SDL_Color statusRegisterHighColor_  = { 255,   0,   0, 255 };
        SDL_Color statusRegisterLowColor_   = {   0, 255,   0, 255 };
        SDL_Color highlightColor_            = makeColor(0x00F0FF);

        std::vector<SDL_Texture*> statusRegisterSymbols;
};

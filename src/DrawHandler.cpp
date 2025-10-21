
#include "DrawHandler.hpp"

#include <sstream>
#include <iostream>

DrawHandler::DrawHandler(SDL_Renderer* renderer)
    : renderer_(renderer)
{
    font_ = TTF_OpenFont("assets/fonts/PixelCode.ttf", FONT_SIZE);
    if (!font_) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
    }

    createCharacterTextures("NV-BDIZC", fontColor_, statusRegisterSymbols);
}

DrawHandler::~DrawHandler()
{
    if (font_) {
        TTF_CloseFont(font_);
    }
}

void DrawHandler::drawFrame()
{
    SDL_SetRenderDrawColor(renderer_, 20, 20, 20, 255); // Background
    SDL_RenderClear(renderer_);

    //SDL_FRect outline = { 100.5f, 100.5f, 200.0f, 150.0f };
    //SDL_SetRenderDrawColor(renderer_, 255, 255, 0, 255);
    //SDL_RenderRect(renderer_, &outline);
}

std::pair<int , int> DrawHandler::drawText(std::string text, int x, int y)
{ // TODO only rerender texture that changes, highlight changes possibly, find changed texture by caching and coordinates
    std::istringstream stream(text);
    std::string line;
    float yOffset = 0.0f;

    int bottomX = 0;
    int bottomY = 0;

    while (std::getline(stream, line)) {
        if (line.empty()) { // Skip empty lines
            yOffset += TTF_GetFontHeight(font_);
            continue;
        }

        SDL_Surface* surface = TTF_RenderText_Blended(font_, line.c_str(), line.length(), fontColor_);
        if (!surface) {
            SDL_Log("Failed to render text surface: %s", SDL_GetError());
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
        if (!texture) {
            SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
            SDL_DestroySurface(surface);
            continue;
        }

        SDL_FRect dst = { float(x), float(y) + yOffset, float(surface->w), float(surface->h) };
        bottomX = x + surface->w;
        bottomY = y + yOffset + surface->h;
        SDL_RenderTexture(renderer_, texture, nullptr, &dst);

        yOffset += surface->h;

        SDL_DestroySurface(surface);
        SDL_DestroyTexture(texture);
    }

    return { bottomX, bottomY };
}

void DrawHandler::drawStatusRegister(uint8_t statusRegister, int x, int y)
{
    for (int i = 0; i < 8; i++) {
        SDL_Texture* texture = statusRegisterSymbols[i];
        
        float texW, texH;
        SDL_GetTextureSize(texture, &texW, &texH);
        SDL_FRect dst = { float(x + i * (texW + 10)), float(y), float(texW), float(texH) };

        if ((statusRegister >> i) & 0x01)
        {
            SDL_SetTextureColorMod(texture, 255, 0, 0);
        }
        else
        {
            SDL_SetTextureColorMod(texture, 0, 255, 0);
        }
        SDL_RenderTexture(renderer_, texture, nullptr, &dst);
    }
}

void DrawHandler::createCharacterTextures(std::string text, SDL_Color textColor, std::vector<SDL_Texture*>& output)
{
    for (char c : text) {
        std::string s(1, c);

        SDL_Surface* surface = TTF_RenderText_Blended(font_, s.c_str(), 1, textColor);
        if (!surface) {
            SDL_Log("Failed to render '%c': %s", c, SDL_GetError());
            continue;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
        if (!texture) {
            SDL_Log("Failed to create texture for '%c': %s", c, SDL_GetError());
            SDL_DestroySurface(surface);
            continue;
        }

        output.push_back(texture);

        SDL_DestroySurface(surface);
    }
}

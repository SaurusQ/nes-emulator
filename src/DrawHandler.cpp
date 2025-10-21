
#include "DrawHandler.hpp"

#include <sstream>

DrawHandler::DrawHandler(SDL_Renderer* renderer)
    : renderer_(renderer)
{
    font_ = TTF_OpenFont("assets/fonts/PixelCode.ttf", 24);
    if (!font_) {
        SDL_Log("Failed to load font: %s", SDL_GetError());
        return;
    }
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

void DrawHandler::drawText(std::string text, int x, int y)
{
    std::istringstream stream(text);
    std::string line;
    float yOffset = 0.0f;

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
        SDL_RenderTexture(renderer_, texture, nullptr, &dst);

        yOffset += surface->h;

        SDL_DestroySurface(surface);
        SDL_DestroyTexture(texture);
    }
}

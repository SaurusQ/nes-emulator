
#include "DrawHandler.hpp"

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

    SDL_FRect outline = { 100.5f, 100.5f, 200.0f, 150.0f };
    SDL_SetRenderDrawColor(renderer_, 255, 255, 0, 255);
    SDL_RenderRect(renderer_, &outline);
}

void DrawHandler::drawText(std::string text, int x, int y)
{
    SDL_Surface* surface = TTF_RenderText_Blended(font_, text.c_str(), text.length(), fontColor_);
    if (!surface) {
        SDL_Log("Failed to render text to surface: %s", SDL_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    if (!texture) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return;
    }
    
    // Get the width and height of the texture
    SDL_FRect dst = { float(x), float(y), float(surface->w), float(surface->h) };
    SDL_RenderTexture(renderer_, texture, nullptr, &dst);
    
    SDL_DestroySurface(surface);
    SDL_DestroyTexture(texture);
}

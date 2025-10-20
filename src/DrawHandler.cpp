
#include "DrawHandler.hpp"

void DrawHandler::drawFrame(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // Background
    SDL_RenderClear(renderer);

    SDL_FRect outline = { 100.5f, 100.5f, 200.0f, 150.0f };
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderRect(renderer, &outline);

    SDL_RenderPresent(renderer);
}


#include "EventHandler.hpp"

bool EventHandler::sdlPollEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return true;
        }

        if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
                case SDLK_ESCAPE:
                    return true;
                default:
                    break;
            }
        }
    }
    return false;
}
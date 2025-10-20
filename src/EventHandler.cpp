
#include "EventHandler.hpp"

bool EventHandler::sdlPollEvent()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            return true;
        }
    }
    return false;
}
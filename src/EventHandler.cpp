
#include "EventHandler.hpp"

#include <algorithm>

EventHandler::EventHandler()
{

}

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

        if (event.type == SDL_EVENT_MOUSE_WHEEL) {
            
            float mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            
            int y = event.wheel.y; // vertical scroll

            if (mouseX >= memoryScrollArea.x && mouseX <= memoryScrollArea.xb
                && mouseY >= memoryScrollArea.y && mouseY <= memoryScrollArea.yb)
            {
                SDL_Keymod mods = SDL_GetModState();

                if (y > 0) {
                    if (mods & SDL_KMOD_CTRL) memoryPointer -= 0x80;
                    else memoryPointer -= 0x10;
                    memoryPointer = std::min(memoryPointer, static_cast<uint16_t>( - (8 * 16)));
                } else if (y < 0) {
                    if (mods & SDL_KMOD_CTRL) memoryPointer += 0x80;
                    else memoryPointer += 0x10;
                    if (static_cast<uint16_t>(memoryPointer + 0x80) < 0x80)
                    {
                        memoryPointer = 0x0000;
                    }
                }
            }
        }
    }
    return false;
}
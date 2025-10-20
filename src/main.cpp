
#include "EventHandler.hpp"
#include "DrawHandler.hpp"
#include "nes/NES.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    SDL_Window *window;
    bool done = false;

    window = SDL_CreateWindow(
        "NES Emulator",
        640,    // width
        480,    // height
        SDL_WINDOW_RESIZABLE    // flags
    );

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return -1;
    }

    const char* backend = SDL_GetCurrentVideoDriver();
    std::cout << "SDL3 backend: " <<  backend << std::endl;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetRenderLogicalPresentation(renderer, 800, 600, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    NES nes;
    nes.powerOn();

    const uint32_t interval = 500; // ms
    uint32_t lastTime = SDL_GetTicks();

    while (!done) {
        SDL_Event event;

        done = EventHandler::sdlPollEvent();

        uint32_t currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= interval) {
            nes.runCycle();
            lastTime = currentTime;
        }

        DrawHandler::drawFrame(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

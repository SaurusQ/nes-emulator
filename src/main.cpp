
#include "EventHandler.hpp"
#include "DrawHandler.hpp"
#include "nes/NES.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

constexpr int screenWidth   = 1920;
constexpr int screenHeight  = 1080;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    SDL_Window *window;
    bool done = false;

    window = SDL_CreateWindow(
        "NES Emulator",
        screenWidth,
        screenHeight,
        SDL_WINDOW_RESIZABLE
    );

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return -1;
    }

    const char* backend = SDL_GetCurrentVideoDriver();
    std::cout << "SDL3 backend: " <<  backend << std::endl;

    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetRenderLogicalPresentation(renderer, screenWidth, screenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    DrawHandler drawHandler(renderer);

    NES nes;
    nes.powerOn();

    std::string memoryStr;
    std::string registerStr;
    uint8_t statusRegister;

    int previousBottomX = 0;
    int previousBottomY = 0;
    int statusRegisterY = 0;

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

        memoryStr = nes.getMemory().getMemoryRegionStr(0x0000, 8 * 16);
        registerStr = nes.getCpu().getRegisterStatusStr(statusRegister);
        
        drawHandler.drawFrame();
        std::tie(previousBottomX, previousBottomY) = drawHandler.drawText(memoryStr, 10, 10);
        statusRegisterY = previousBottomY;
        std::tie(previousBottomX, previousBottomY) = drawHandler.drawText(registerStr, 10, previousBottomY + 10);
        drawHandler.drawStatusRegister(statusRegister, 150, statusRegisterY + 10);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

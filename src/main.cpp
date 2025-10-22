
#include "EventHandler.hpp"
#include "DrawHandler.hpp"
#include "nes/Instruction.hpp"
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

    constexpr int statusPanelX = 10;
    constexpr int statusPanelY =  10;

    std::string memoryStr;
    std::string registerStr;
    std::string instructionStr;
    uint8_t statusRegister;

    int previousBottomX = 0;
    int previousBottomY = 0;
    int statusRegisterY = 0;

    const uint32_t interval = 500; // ms
    uint32_t lastTime = SDL_GetTicks();

    while (!done) {
        done = EventHandler::sdlPollEvent();

        uint32_t currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= interval) {
            nes.runCycle();
            lastTime = currentTime;
        }

        memoryStr = nes.getMemory().getMemoryRegionStr(0x0000, 8 * 16);
        registerStr = nes.getCpu().getRegisterStatusStr(statusRegister);
        instructionStr = Instruction::getInstructionListString(nes.getCpu().getCurrentAddress(), nes.getMemory(), 3);
        

        drawHandler.drawFrame();

        // Status panel
        std::tie(previousBottomX, previousBottomY) = drawHandler.drawText(memoryStr, statusPanelX, statusPanelY);
        statusRegisterY = previousBottomY;
        std::tie(previousBottomX, previousBottomY) = drawHandler.drawText(registerStr, statusPanelX, previousBottomY + 20);
        drawHandler.drawStatusRegister(statusRegister, statusPanelX + 150, statusRegisterY + 20);
        std::tie(previousBottomX, previousBottomY) = drawHandler.drawText(nes.getCpu().getCurrentCycleStr(), statusPanelX, previousBottomY + 10);
        std::tie(previousBottomX, previousBottomY) = drawHandler.drawText(instructionStr, statusPanelX, previousBottomY + 20, true);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

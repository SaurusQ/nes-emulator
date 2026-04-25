
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

    screenBufferTexture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 283, 242);
    if (!screenBufferTexture_) {
        SDL_Log("Failed to create screen buffer texture: %s", SDL_GetError());
    }
    patternTableTexture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 8 * 16 * 2, 8 * 16);
    if (!patternTableTexture_) {
        SDL_Log("Failed to create pattern table texture: %s", SDL_GetError());
    }
}

DrawHandler::~DrawHandler()
{
    if (font_)
    {
        TTF_CloseFont(font_);
    }

    if (screenBufferTexture_)
    {
        SDL_DestroyTexture(screenBufferTexture_);
    }
    if (patternTableTexture_)
    {
        SDL_DestroyTexture(patternTableTexture_);
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

std::pair<int , int> DrawHandler::drawText(std::string text, int x, int y, bool highlightFirst)
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

        if (highlightFirst && yOffset == 0)
        {
            SDL_SetTextureColorMod(texture, highlightColor_.r, highlightColor_.g, highlightColor_.b);
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

void DrawHandler::drawPPU(const std::vector<PPU::Pixel>& screenBuffer, const SDL_FRect& dst)
{
    SDL_UpdateTexture(
        screenBufferTexture_,
        NULL,
        screenBuffer.data(),
        283 * sizeof(PPU::Pixel)
    );

    SDL_RenderTexture(renderer_, screenBufferTexture_, NULL, &dst);
}

void DrawHandler::drawPatternTable(const uint8_t* patternTable, const SDL_FRect& dst)
{
    const int texWidth = 256;
    const int texHeight = 128;

    static std::vector<SDL_Color> viewBuffer(texWidth * texHeight);

    const SDL_Color palette[4] = {
        { 0,   0,   0,   255 }, // Index 0: Transparent/Black
        { 85,  85,  85,  255 }, // Index 1: Light Gray
        { 170, 170, 170, 255 }, // Index 2: Dark Gray
        { 255, 255, 255, 255 }  // Index 3: White
    };

    for (int table = 0; table < 2; table++) {
        int tableOffset = table * 0x1000;
        int renderXOffset = table * 128;

        for (int spriteX = 0; spriteX < 16; spriteX++) {
            for (int spriteY = 0; spriteY < 16; spriteY++) {
                int dataPtr = tableOffset + spriteX * 8 + spriteY * 8 * 16;

                for (int tileY = 0; tileY < 8; tileY++) {
                    int lowPlane  = patternTable[dataPtr + tileY];
                    int highPlane = patternTable[dataPtr + tileY + 8];
                    for (int tileX = 0; tileX < 8; tileX++) {
                        const SDL_Color& color = palette[
                            ((lowPlane  >> (7 - tileX)) & 0x01) | 
                           (((highPlane >> (7 - tileX)) & 0x01) << 1)
                        ];
                        int pixelX = renderXOffset + (spriteX * 8) + tileX;
                        int pixelY = (spriteY * 8) + tileY;
                        viewBuffer[pixelY * texWidth + pixelX] = color;
                    }
                }
            }
        }
    }


    SDL_UpdateTexture(
        patternTableTexture_,
        NULL,
        viewBuffer.data(),
        sizeof(SDL_Color) * texWidth
    );

    SDL_RenderTexture(renderer_, patternTableTexture_, NULL, &dst);
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

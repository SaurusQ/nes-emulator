#pragma once

#include <cstdint>

struct InternalRegisters
{
    uint16_t v;         // Current VRAM address (15 bits)
    uint16_t t;         // Temporary VRAM address (15 bits)
    uint8_t x;          // Fine X scroll (3 bits)
    uint8_t w;          // First or second write toggle (1 bit)
};

typedef union
{
    struct
    {
        uint8_t N : 2;  // Base nametable address (0 = $2000; 1 = $2400; 2 = $2800; 3 = $2C00)
        bool I : 1;     // VRAM address increment per CPU read/write of PPUDATA (0: add 1, going across; 1: add 32, going down)
        bool S : 1;     // Sprite pattern table address for 8x8 sprites (0: $0000; 1: $1000; ignored in 8x16 mode)
        bool B : 1;     // Background pattern table address (0: $0000; 1: $1000)
        bool H : 1;     // Sprite size (0: 8x8 pixels; 1: 8x16 pixels – see PPU OAM#Byte 1)
        bool P : 1;     // PPU master/slave select (0: read backdrop from EXT pins; 1: output color on EXT pins)
        bool V : 1;     // Vblank NMI enable (0: off, 1: on)
    };
    uint8_t reg;

} PPUCTRL;

typedef union
{
    struct
    {
        bool G : 1;     // Greyscale (0: normal color, 1: greyscale)
        bool m : 1;     // 1: Show background in leftmost 8 pixels of screen, 0: Hide
        bool M : 1;     // 1: Show sprites in leftmost 8 pixels of screen, 0: Hide
        bool b : 1;     // 1: Enable background rendering
        bool s : 1;     // 1: Enable sprite rendering
        bool R : 1;     // Emphasize red (green on PAL/Dendy)
        bool G : 1;     // Emphasize green (red on PAL/Dendy)
        bool B : 1;     // Emphasize blue 

    };
    uint8_t reg;
} PPUMASK;

typedef union
{
    struct
    {
        uint8_t X : 5;  // (PPU open bus or 2C05 PPU identifier)
        bool O: 1;      // Sprite overflow flag
        bool S: 1;      // Sprite 0 hit flag
        bool V: 1;      // Vblank flag, cleared on read. Unreliable; check wiki
    };
    uint8_t reg;
} PPUSTATUS;

typedef uint16_t OAMADDR; // Sprite RAM address
typedef uint16_t OAMDATA; // Sprite RAM data

typedef uint16_t PPUSCROLL; // Used to change the scroll position
typedef uint16_t PPUADDR;   // VRAM address
typedef uint8_t  PPUDATA;   // VRAM data
typedef uint8_t  OAMDMA;    // Sprite DMA

struct Registers
{
    PPUCTRL ppuctrl;
    PPUMASK ppumask;
    PPUSTATUS ppustatus;
    OAMADDR oamaddr;
    OAMDATA oamdata;
    PPUSCROLL ppuscroll;
    PPUADDR ppuaddr;
    PPUDATA ppudata;
    OAMDMA oamdma;
    InternalRegisters internal;
};


#include "PPU.hpp"

namespace PPU
{
    PPU::PPU(Bus& bus)
        : bus_(bus)
    {
        reg_.ppuctrl.reg    = 0x00;
        reg_.ppumask.reg    = 0x00;
        reg_.ppustatus.reg  = 0b10100000;
        reg_.oamaddr        = 0x00;
        reg_.oamdata        = 0x00;
        reg_.ppuscroll      = 0x00;
        reg_.ppuaddr        = 0x00;
        reg_.ppudata        = 0x00;
        reg_.oamdma         = 0x00;
        reg_.internal.w     = 0;
    
        screenBuffer_.resize(283 * 242);
        std::fill(screenBuffer_.begin(), screenBuffer_.end(), Pixel{100, 0, 0});
    }
    
    void PPU::reset()
    {
        reg_.ppuctrl.reg    = 0x00;
        reg_.ppumask.reg    = 0x00;
        reg_.ppuscroll      = 0x00;
        reg_.ppudata        = 0x00;
        reg_.internal.w     = 0;
    }
    
    void PPU::tick()
    {
        // 1. Fetch a nametable entry from $2000-$2FFF.
        reg_.internal.v = getBaseNameTableAddress();
        
        // 2. Fetch the corresponding attribute table entry from $23C0-$2FFF and increment the current VRAM address within the same row.
        
        
        // 3. Fetch the low-order byte of an 8x1 pixel sliver of pattern table from $0000-$0FF7 or $1000-$1FF7.
        // 4. Fetch the high-order byte of this sliver from an address 8 bytes higher.
        // 5. Turn the attribute data and the pattern table data into palette indices, and combine them with data from sprite data using priority.
    }

    uint16_t PPU::getBaseNameTableAddress()
    {
        constexpr uint16_t baseAddressMap[] = { 0x2000, 0x2400, 0x2800, 0x2C00 };
        return baseAddressMap[reg_.ppuctrl.N];
    }
    
    uint16_t PPU::getSpritePatternTableAddress()
    {
        constexpr uint16_t spritePatternTableMap[] = { 0x0000, 0x1000 }; // TODO 8x16 ignores
        return spritePatternTableMap[static_cast<uint8_t>(reg_.ppuctrl.N)];
    }
}

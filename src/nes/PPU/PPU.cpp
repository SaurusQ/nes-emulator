
#include "PPU.hpp"

PPU::PPU()
{

}

PPU::~PPU()
{

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

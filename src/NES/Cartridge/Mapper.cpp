#include "Mapper.hpp"


void Mapper::attach(PPU::PPU& ppu, Cartridge::Cartridge& cartridge, RAM& ram, VRAM& vram)
{
    ppu_        = ppu;
    cartridge_  = cartridge;
    ram_        = ram;
    vram_       = vram;
}

void Mapper::readCPU(uint16_t address, uint8_t& data) const
{
    if (address < 0x2000) // RAM
    {
        ram_.read(0x07FF & address, data); // Mirrored banks
    }
    else if (address < 0x4000) // PPU
    {
        ppu_.read(0x0007 & address, data); // Mirrored every 8 bytes
    }
    else if (address < 0x4020) // APU & I/O
    {
        // Pass for now
    }
    this->mapperReadCPU(address, data);
}

void Mapper::storeCPU(uint16_t address, uint8_t data)
{
    if (address < 0x2000) // RAM
    {
        ram_.store(0x07FF & address, data); // Mirrored banks
    }
    else if (address < 0x4000) // PPU
    {
        ppu_.store(0x0007 & address, data); // Mirrored every 8 bytes
    }
    else if (address < 0x4020) // APU & I/O
    {
        // Pass for now
    }
    this->mapperStoreCPU(address, data);
}

void Mapper::readPPU(uint16_t address, uint8_t& data) const
{

}

void Mapper::storePPU(uint16_t address, uint8_t data)
{

}

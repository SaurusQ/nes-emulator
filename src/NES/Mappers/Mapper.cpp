#include "Mapper.hpp"

Mapper::Mapper()
{

}

void Mapper::readCPU(uint16_t address, uint8_t& data) const
{
    if (address < 0x2000) // RAM
    {
        //cpu_.getRAM().read(0x07FF & address, data); // Mirrored banks
    }
    else if (address < 0x4000) // PPU
    {
        //ppu_.read(address % 8, data); // Mirrored every 8 bytes
    }
    else if (address < 0x4020) // APU & I/O
    {
        // Pass for now
    }
    else
    {
        //mapper_.read<Addressspace::CPU>(address, data);
    }
}

void Mapper::readPPU(uint16_t address, uint8_t& data) const
{

}

void Mapper::storeCPU(uint16_t address, uint8_t data)
{

}

void Mapper::storePPU(uint16_t address, uint8_t data)
{

}

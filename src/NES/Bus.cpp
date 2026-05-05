#include "Bus.hpp"


Bus::Bus(Mapper* mapper, PPU::Registers& ppu, RAM& ram)
    : mapper_(mapper)
    , ppu_(ppu)
    , ram_(ram)
{

}

void Bus::readCPU(uint16_t address, uint8_t& data)
{
    bool mapped = false;
    if (address < 0x2000) // RAM
    {
        mapped = true;
        ram_.read(0x07FF & address, data); // Mirrored banks
    }
    else if (address < 0x4000) // PPU
    {
        mapped = true;
        ppu_.read(0x0007 & address, data); // Mirrored every 8 bytes
    }
    else if (address < 0x4020) // APU & I/O
    {
        mapped = true; // TODO
        // Pass for now
    }

    mapped |= mapper_->readCPU(address, data);
    
    if (!mapped) // Open bus behavior: return last value on the bus
    {
        data = lastReadCPU_;
    }
    lastReadCPU_ = data;
}

void Bus::storeCPU(uint16_t address, uint8_t data)
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

    mapper_->storeCPU(address, data);
}


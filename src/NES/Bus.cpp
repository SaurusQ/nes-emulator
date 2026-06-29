#include "Bus.hpp"

#include <iostream>

Bus::Bus(CPU_t *cpu, PPU_t *ppu, RAM *ram, VRAM *vram)
    : cpu_(cpu), ppu_(ppu), ram_(ram), vram_(vram)
{

}

void Bus::peekCPU(uint16_t address, uint8_t& data) const
{
    if (address <= 0x1FFF)
    {
        ram_->read(address & 0x07FF, data);
    }
    else if (address <= 0x3FFF)
    {
        ppu_->read(address & 0x0007, data);
    }
    else if (address <= 0x5FFF)
    {
        // APU AND IO REGISTERS TODO
    }
    else if (address <= 0x401F)
    {
        mapper_->readCPU(address & 0x1FFF, data);
    }
}

void Bus::readCPU(uint16_t address, uint8_t& data)
{
    data = lastRead_;

    if (address <= 0x1FFF)
    {
        ram_->read(address & 0x07FF, data);
    }
    else if (address <= 0x3FFF)
    {
        ppu_->read(address & 0x0007, data);
    }
    else if (address <= 0x5FFF)
    {
        // APU AND IO REGISTERS TODO
    }
    else if (address <= 0x401F)
    {
        mapper_->readCPU(address & 0x1FFF, data);
    }

    lastRead_ = data;
}

void Bus::storeCPU(uint16_t address, uint8_t data)
{
    if (address <= 0x1FFF)
    {
        ram_->store(address & 0x07FF, data);
    }
    else if (address <= 0x3FFF)
    {
        ppu_->store(address & 0x0007, data);
    }
    else if (address <= 0x5FFF)
    {
        // APU AND IO REGISTERS TODO
    }
    else if (address <= 0x401F)
    {
        mapper_->storeCPU(address & 0x1FFF, data);
    }
}

void Bus::readPPU(uint16_t address, uint8_t& data)
{
    (void)address;
    data = 0xFF;
}

void Bus::storePPU(uint16_t address, uint8_t data)
{
    (void)address;
    (void)data;
}

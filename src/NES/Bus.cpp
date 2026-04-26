#include "Bus.hpp"

Bus::Bus(CPU::CPU cpu, PPU::PPU ppu, Cartridge::Mapper mapper)
{
    cpu_ = cpu;
    ppu_ = ppu;
    mapper_ = mapper;
}

template<Addressspace AS>
void Bus::read()
{
    if (AS == Addressspace::CPU)
    {
        cpu_.read(address, data);
    }
    else if (AS == Addressspace::PPU)
    {
        ppu_.read(address, data);
    }
}

template<Addressspace AS>
void Bus::write()
{

}

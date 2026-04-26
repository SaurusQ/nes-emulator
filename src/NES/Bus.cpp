#include "Bus.hpp"

Bus::Bus(CPU::CPU& cpu, PPU::PPU& ppu, Cartridge::Mapper& mapper)
    : cpu_(cpu)
    , ppu_(ppu)
    , mapper_(mapper)
{

}

template<Addressspace AS>
void Bus::read(uint16_t address, uint8_t& data)
{
    if constexpr (AS == Addressspace::CPU)
    {
        if address < 0x2000 // RAM
        {
            cpu_.getRAM().read(0x07FF & address, data); // Mirrored banks
            return;
        }
        if address < 0x4000; // PPU
        {
            ppu_
        }
    }
    else if constexpr (AS == Addressspace::PPU)
    {
        ppu_.read(address, data);
    }
}

template<Addressspace AS>
void Bus::write(uint16_t address, uint8_t data)
{

}

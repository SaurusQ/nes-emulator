#include "Memory.hpp"

#include <memory>
#include <cstring>
#include <iostream>


constexpr size_t MEMORY_SIZE = 65536;

Memory::Memory()
{
    memory_ = std::make_unique<uint8_t[]>(MEMORY_SIZE);
    std::memset(memory_.get(), 0x00, MEMORY_SIZE);

    std::cout << "Memory initialized" << std::endl;
}

Memory::~Memory()
{

}

void Memory::loadData(uint16_t startAddress, const uint8_t* data, size_t size)
{
    if (startAddress + size > MEMORY_SIZE)
    {
        std::cerr << "Error: Address exceeds memory region" << std::endl;
        return;
    }

    std::memcpy(memory_.get() + startAddress, data, size);
}

void Memory::fetch(uint16_t address, uint8_t& data) const
{
    data = memory_[address];
}

void Memory::store(uint16_t address, uint8_t data)
{
    memory_[address] = data;
}


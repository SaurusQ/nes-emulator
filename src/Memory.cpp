#include "Memory.hpp"

#include <memory>
#include <cstring>
#include <iostream>


constexpr size_t RAM_SIZE = 65536;

Memory::Memory()
{
    memory_ = std::make_unique<uint8_t[]>(RAM_SIZE);
    std::memset(memory_.get(), 0x00, RAM_SIZE);

    std::cout << "RAM initialized" << std::endl;
}

Memory::~Memory()
{

}

void Memory::fetch(uint16_t address, uint8_t& data) const
{
    data = memory_[address];
}

void Memory::store(uint16_t address, uint8_t data)
{
    memory_[address] = data;
}


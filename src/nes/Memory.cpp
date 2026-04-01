#include "Memory.hpp"

#include <memory>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>


constexpr size_t MEMORY_SIZE = 0x010000;

Memory::Memory()
{
    memory_ = std::make_unique<uint8_t[]>(MEMORY_SIZE);
    std::fill(memory_.get(), memory_.get() + MEMORY_SIZE, 0xEA); // Fill with NOP

    std::cout << "Memory initialized" << std::endl;
}

void Memory::loadData(uint16_t startAddress, const uint8_t* data, size_t size)
{
    if (startAddress + size > MEMORY_SIZE)
    {
        std::cerr << "Error: Address exceeds memory region" << std::endl;
        return;
    }

    std::copy(data, data + size, memory_.get() + startAddress);
}

void Memory::read(uint16_t address, uint8_t& data) const
{
    data = memory_[address];
}

void Memory::store(uint16_t address, uint8_t data)
{
    memory_[address] = data;
}

std::string Memory::getMemoryRegionStr(uint16_t address, size_t size) const
{
    std::ostringstream oss;
    oss << std::hex << std::uppercase;
    std::string start = "";
    for (size_t i = 0; i < size && address + i < MEMORY_SIZE; i++)
    {
        if (i % 8 == 0)
        {
            oss << start << "$" << std::setw(4) << std::setfill('0') << address + i;
            start = "\n";
        }
        oss << " " << std::setw(2) << std::setfill('0') << static_cast<int>(memory_[address + i]);
    }
    return oss.str();
}

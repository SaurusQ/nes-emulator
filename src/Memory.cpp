#pragma once

#include "RAM.hpp"

#include <memory>
#include <cstring>
#include <iostream>


constexpr size_t RAM_SIZE = 65536;

RAM::RAM()
{
    memory_ = std::make_unique<uint8_t[]>(RAM_SIZE);
    std::memset(memory_.get(), 0x00, RAM_SIZE);

    std::cout << "RAM initialized" << std::endl;
}

RAM::~RAM()
{

}

void RAM::fetch(uint16_t address, uint8_t& data) const
{
    data = memory_[address];
}

void RAM::store(uint16_t address, uint8_t data)
{
    memory_[address] = data;
}


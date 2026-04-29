#pragma once

#include "Addressable.hpp"

#include <cstdint>
#include <string>

constexpr size_t NES_CPU_RAM_SIZE = 0x0800;

class RAM : public Addressable
{
    public:
        RAM() = default;
        ~RAM() = default;

        size_t size() const { return NES_CPU_RAM_SIZE; };
    protected:
        inline uint8_t* getMemoryPtr() { return ram_; };
    private:
        uint8_t ram_[NES_CPU_RAM_SIZE];
};

#pragma once

#include "Addressable.hpp"

#include <cstdint>
#include <string>

constexpr size_t NES_CPU_RAM_SIZE = 0x0800;
namespace CPU
{
    class RAM : public Addressable
    {
        public:
            RAM() = default;
            ~RAM() = default;

            void read(uint16_t address, uint8_t& data) const { data = ram_[address]; };
            void store(uint16_t address, uint8_t data)       { ram_[address] = data; };
            size_t size() const { return NES_CPU_RAM_SIZE; };
            const uint8_t* getMemoryPtr() const {  return ram_; }
            
            std::string getMemoryRegionStr(uint16_t address, size_t size) const;
        private:
            uint8_t ram_[NES_CPU_RAM_SIZE];
    };
}

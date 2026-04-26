#pragma once

#include "Addressable.hpp"

#include <cstdint>
#include <string>

namespace CPU
{
    class RAM : public Addressable
    {
        public:
            RAM() = default;
            ~RAM() = default;

            void read(uint16_t address, uint8_t& data) const;
            void store(uint16_t address, uint8_t data);
            size_t size() const;
            std::string getMemoryRegionStr(uint16_t address, size_t size) const;
            uint8_t* getMemoryPtr() const;
        private:
            uint8_t ram_[0x0800];
    };
}

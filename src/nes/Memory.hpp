#pragma once

#include "Definitions.hpp"

#include <memory>


class Memory
{
    public:
        Memory();
        ~Memory();
        
        void loadData(uint16_t startAddress, const uint8_t* programData, size_t size);

        void fetch(uint16_t address, uint8_t& data) const;
        void store(uint16_t address, uint8_t data);

        std::string getMemoryRegionStr(uint16_t address, size_t size) const;

    private:
        std::unique_ptr<uint8_t[]> memory_;
};

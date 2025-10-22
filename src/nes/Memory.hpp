#pragma once

#include "Definitions.hpp"

#include <memory>


class Memory
{
    friend class Instruction;
    public:
        Memory();
        ~Memory();
        
        void loadData(uint16_t startAddress, const uint8_t* programData, size_t size);

        void read(uint16_t address, uint8_t& data) const;
        void store(uint16_t address, uint8_t data);

        size_t size() const { return 65000; /* TODO */ }

        std::string getMemoryRegionStr(uint16_t address, size_t size) const;

        uint8_t* getMemoryPtr() const { return memory_.get(); }

    private:
        std::unique_ptr<uint8_t[]> memory_;
};

#pragma once

#include "Definitions.hpp"

#include <memory>


class Memory
{
    template<InstructionType IT, AddressingMode AM>
    friend class Instruction;
    public:
        Memory();
        ~Memory() = default;
        
        void loadData(uint16_t startAddress, const uint8_t* programData, size_t size);

        void read(uint16_t address, uint8_t& data) const;
        void store(uint16_t address, uint8_t data);

        size_t size() const { return 65000; /* TODO */ }

        std::string getMemoryRegionStr(uint16_t address, size_t size) const;

        uint8_t* getMemoryPtr() const { return memory_.get(); }

        const uint8_t* getPatternTable() const { return memory_.get() + 0x1000; }

    private:
        std::unique_ptr<uint8_t[]> memory_;
};

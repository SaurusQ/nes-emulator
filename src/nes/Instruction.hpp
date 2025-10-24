#pragma once

#include "Definitions.hpp"
#include "CPU.hpp"
#include "Memory.hpp"
#include "Instructions.inl"

#include <string>

using OperationFunc = void (*)(Registers*, uint8_t);

class Instruction
{
    public:
        Instruction() // Default constructor for std::array
            : operation_(NOP), opcode_(0x00), name_("UNK"), mode_(AddressingMode::IMPLICIT), bytes_(1), cycles_(2), cyclesPageCrossed_(2) {}
        Instruction(uint8_t opcode, const char* name, OperationFunc operation, AddressingMode mode, uint8_t bytes, uint8_t cycles);
        Instruction(uint8_t opcode, const char* name, OperationFunc operation, AddressingMode mode, uint8_t bytes, uint8_t cycles, uint8_t cyclesPageCrossed);
        ~Instruction() = default;

        inline uint8_t execute(CPU* cpu) const {
            uint8_t mem = 0x00;
            uint16_t targetAddress = 0x0000;
            bool pageCrossed = false;

            cpu->fetch(mode_, targetAddress, mem, pageCrossed);

            operation_(&cpu->registers_, mem);

            return pageCrossed ? cyclesPageCrossed_ : cycles_;
        }

        std::string getStr(uint8_t* memory) const;

        size_t getLenght() const { return bytes_; }

        static std::string getInstructionListString(uint16_t address, const Memory& memory, unsigned int count);
    protected:
        OperationFunc   operation_;
        uint8_t         opcode_;
        const char*     name_;
        AddressingMode  mode_;
        uint8_t         bytes_;
        uint8_t         cycles_;
        uint8_t         cyclesPageCrossed_;
};

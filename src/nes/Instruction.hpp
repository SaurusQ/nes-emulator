#pragma once

#include "Definitions.hpp"
#include "CPU.hpp"
#include "Memory.hpp"

#include <string>


class Instruction
{
    public:
        Instruction(uint8_t opcode, const char* name, AddressingMode mode, uint8_t bytes, uint8_t cycles);
        Instruction(uint8_t opcode, const char* name, AddressingMode mode, uint8_t bytes, uint8_t cycles, uint8_t cyclesPageCrossed);
        ~Instruction();

        virtual uint8_t execute(CPU* cpu) const {
            uint8_t mem = 0x00;
            uint16_t targetAddress = 0x0000;
            bool pageCrossed = false;

            cpu->fetch(mode_, targetAddress, mem, pageCrossed);

            operation(cpu, mem);

            return pageCrossed ? cyclesPageCrossed_ : cycles_;
        }

        virtual void operation(CPU* cpu, uint8_t mem) const = 0;
        virtual std::string getStr(uint8_t* memory);

        size_t getLenght() const { return bytes_; }

        static std::string getInstructionListString(uint16_t address, const Memory& memory, unsigned int count);
    protected:
        const uint8_t         opcode_;
        const char*           name_;
        const AddressingMode  mode_;
        const uint8_t         bytes_;
        const uint8_t         cycles_;
        const uint8_t         cyclesPageCrossed_;
};

class ADC : public Instruction
{
    public:
        using Instruction::Instruction;
        virtual void operation(CPU* cpu, uint8_t mem) const;
};

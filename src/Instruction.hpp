#pragma once

#include "Definitions.hpp"
#include "CPU.hpp"
#include "Memory.hpp"

#include <string>

using OpcodeFunction = uint8_t(*)(CPU& cpu, Memory& memory);

class Instruction
{
    public:
        Instruction(std::string name, uint8_t opcode, AddressingMode mode, uint8_t bytes, uint8_t cycles, OpcodeFunction method);
        Instruction(std::string name, uint8_t opcode, AddressingMode mode, uint8_t bytes, uint8_t cycles, uint8_t cyclesPageCrossed, OpcodeFunction method);
        ~Instruction();

        uint8_t execute(CPU& cpu, Memory& memory);

    private:
        std::string     name_;
        uint8_t         opcode_;
        AddressingMode  mode_;
        uint8_t         bytes_;
        uint8_t         cycles_;
        uint8_t         cyclesPageCrossed_;

        OpcodeFunction method_;

        uint8_t ADC(CPU& cpu, Memory& memory);
};

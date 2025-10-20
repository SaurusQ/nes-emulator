#pragma once

#include "Definitions.hpp"
#include "CPU.hpp"
#include "Memory.hpp"

#include <string>


class Instruction
{
    using OpcodeFunction = uint8_t(*)(const Instruction* ins, CPU& cpu, Memory& memory);
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
        
    public:
        static uint8_t ADC(const Instruction* ins, CPU& cpu, Memory& memory);
};

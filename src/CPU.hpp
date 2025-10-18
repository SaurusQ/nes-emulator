#pragma once

#include "Definitions.hpp"
#include "Memory.hpp"

#include <cstdint>

typedef union
{
    struct
    {
        uint8_t C : 1; // Carry
        uint8_t Z : 1; // Zero
        uint8_t I : 1; // Interrupt Disable
        uint8_t D : 1; // Decimal Mode
        uint8_t B : 1; // Break Command
        uint8_t U : 1; // Unused
        uint8_t V : 1; // Overflow
        uint8_t N : 1; // Negative
    };
    uint8_t reg;
} StatusRegister;;

struct Registers
{
    StatusRegister  P;  // Processor Status
    uint16_t        PC; // Program Counter
    uint8_t         SP; // Stack Pointer
    uint8_t         A;  // Accumulator
    uint8_t         X;  // Index Register X
    uint8_t         Y;  // Index Register Y
};

class CPU
{
    public:
        CPU();
        ~CPU();
        void resetRegisters();
        void clockTick();
        bool fetchInstructionData(AddressingMode ad, uint16_t& targetAddress, uint8_t& value);

        void printRegisters() const;
    private:



        Registers registers_;
        Memory memory_;
        uint64_t cycle_ = 0;
};
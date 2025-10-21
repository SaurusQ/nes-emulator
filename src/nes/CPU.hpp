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
        uint8_t U : 1; // Unused (Always one)
        uint8_t V : 1; // Overflow
        uint8_t N : 1; // Negative
    };
    uint8_t reg;
} StatusRegister;

struct Registers
{
    StatusRegister  P;  // Processor Status
    uint16_t        PC; // Program Counter (In hardware separate high and low byte registers)
    uint8_t         SP; // Stack Pointer
    uint8_t         A;  // Accumulator
    uint8_t         X;  // Index Register X
    uint8_t         Y;  // Index Register Y
};

class CPU
{
    friend class Instruction;
    public:
        CPU(Memory& memory);
        ~CPU();
        void resetRegisters();
        void clockTick();
        bool readData(AddressingMode am, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed);

        void printStatus() const;
        std::string getRegisterStatusStr() const { return getRegisterStatusStr(false); }
        std::string getRegisterStatusStr(uint8_t& statusRegister) const;
        uint64_t getCurrentCycle() const { return cycle_; }
        std::string getCurrentCycleStr() const { return "Cycles: " + std::to_string(cycle_); }

    private:
        std::string getRegisterStatusStr(bool renderVersion) const;


        Registers registers_;
        Memory& memory_;
        uint64_t cycle_ = 0;
};

#pragma once

#include "Definitions.hpp"
#include "Memory.hpp"

#include <cstdint>

class Instruction;

typedef union
{
    struct
    {
        bool C : 1; // Carry
        bool Z : 1; // Zero
        bool I : 1; // Interrupt Disable
        bool D : 1; // Decimal Mode
        bool B : 1; // Break Command
        bool U : 1; // Unused (Always one)
        bool V : 1; // Overflow
        bool N : 1; // Negative
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
        inline bool fetch(AddressingMode am, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed);

        void printStatus() const;

        std::string getRegisterStatusStr() const { return getRegisterStatusStr(false); }
        std::string getRegisterStatusStr(uint8_t& statusRegister) const;
        uint64_t    getCurrentCycle() const { return cycle_; }
        std::string getCurrentCycleStr() const { return "Cycles: " + std::to_string(cycle_); }
        uint16_t getCurrentAddress() const { return registers_.PC; }
        bool nextInstruction() const { return insCyclesToExecute_ == 0; }
    private:
        std::string getRegisterStatusStr(bool renderVersion) const;

        Registers registers_;
        Memory& memory_;
        uint64_t cycle_ = 0;
        uint64_t insCyclesToExecute_ = 0;
};

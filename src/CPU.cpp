
#include "CPU.hpp"

#include <iostream>

CPU::CPU()
{
    registers_.PC   = 0xFFFC;
    registers_.SP   = 0xFD; // Decremented by 3 after each reset
    registers_.A    = 0x00;
    registers_.X    = 0x00;
    registers_.Y    = 0x00;

    // Status Register initialization
    registers_.P.C = 0x00;
    registers_.P.Z = 0x00;
    registers_.P.I = 0x01; // Disable interrupts
    registers_.P.D = 0x00;
    registers_.P.V = 0x00;
    registers_.P.N = 0x00;

    registers_.P.B = 0x00;
    registers_.P.U = 0x01; // Unused, always 1
}

CPU::~CPU()
{

}

void CPU::clockTick()
{
    uint8_t opcode = 0x00;

    std::cout << "Cycle: " << cycle_ << " PC at: " << std::hex << static_cast<int>(registers_.PC) << std::endl; 

    memory_.fetch(registers_.PC, opcode);
    registers_.PC++;

    
    // TODO instruction decoding and execution

    cycle_++;
}

void CPU::resetRegisters()
{
    registers_.PC = 0xFFFC;
    registers_.SP -= 0x3;
}

bool CPU::fetchInstructionData(AddressingMode ad, uint16_t& targetAddress, uint8_t& value)
{
    targetAddress = 0x0000;

    uint8_t byte = 0x00;

    switch (ad)
    {
        case IMPLICIT:
            return false;
        case ACCUMULATOR:
            value = registers_.A;
            return false;
        case IMMEDIATE:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            value = byte;
            return false;
        case ZERO_PAGE:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            targetAddress = static_cast<uint16_t>(byte);
            memory_.fetch(targetAddress, value);
            registers_.PC++;
            return true;
        case ZERO_PAGE_X:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            byte += registers_.X; // Overflow expected
            targetAddress = static_cast<uint16_t>(byte);
            memory_.fetch(targetAddress, value);
            registers_.PC++;
            return true;
        case ZERO_PAGE_Y:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            byte += registers_.Y; // Overflow expected
            targetAddress = static_cast<uint16_t>(byte);
            memory_.fetch(targetAddress, value);
            registers_.PC++;
            return true;
        case RELATIVE: // Branch instructions
            return false;

        default:
            std::cerr << "Addressing mode not implemented!" << std::endl;
            std::runtime_error("Addressing mode not implemented");
    }
}

void CPU::printStatus() const
{
    std::cout << "CPU Cycles: " << cycle_ << "\n"
            << "PC: " << std::hex << static_cast<int>(registers_.PC) << "\n"
            << "SP: " << std::hex << static_cast<int>(registers_.SP) << "\n"
            << "A: "  << std::hex << static_cast<int>(registers_.A)  << "\n"
            << "X: "  << std::hex << static_cast<int>(registers_.X)  << "\n"
            << "Y: "  << std::hex << static_cast<int>(registers_.Y)  << std::endl;

    std::cout << "Status Register: " << std::hex << static_cast<int>(registers_.P.reg) << std::endl;
}

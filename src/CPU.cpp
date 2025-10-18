
#include "CPU.hpp"

#include <iostream>
#include <iomanip>
#include <bitset>

CPU::CPU(Memory& memory)
    : memory_(memory)
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

    //std::cout << "Cycle: " << cycle_ << " PC at: " << std::hex << static_cast<int>(registers_.PC) << std::endl; 

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

bool CPU::readData(AddressingMode am, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
{
    targetAddress = 0x0000;

    uint8_t byte = 0x00;
    uint8_t lowByte = 0x00;
    uint8_t highByte = 0x00;
    // TODO page crossing detection

    switch (am)
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
        case ABSOLUTE:
            memory_.fetch(registers_.PC, lowByte);
            registers_.PC++;
            memory_.fetch(registers_.PC, highByte);
            registers_.PC++;
            targetAddress = static_cast<uint16_t>(lowByte) | (static_cast<uint16_t>(highByte) << 8);
            memory_.fetch(targetAddress, value);
            registers_.PC++;
            return true;
        default:
            std::cerr << "Addressing mode not implemented!" << std::endl;
            std::runtime_error("Addressing mode not implemented");
    }
}

void CPU::printStatus() const
{
    std::cout << "CPU Cycles: 0x" << cycle_ << "\n"
            << "PC: 0x" << std::setfill('0') << std::setw(4)<< std::hex << static_cast<int>(registers_.PC) << "\n"
            << "SP: 0x" << std::setfill('0') << std::setw(4)<< std::hex << static_cast<int>(registers_.SP) << "\n"
            << "A:  0x"  << std::setfill('0') << std::setw(2)<< std::hex << static_cast<int>(registers_.A)  << "\n"
            << "X:  0x"  << std::setfill('0') << std::setw(2)<< std::hex << static_cast<int>(registers_.X)  << "\n"
            << "Y:  0x"  << std::setfill('0') << std::setw(2)<< std::hex << static_cast<int>(registers_.Y)  << "\n"
            << "Status Register: 0b" << std::bitset<8>(registers_.P.reg) << std::endl;
}

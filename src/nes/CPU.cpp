
#include "CPU.hpp"

#include "OpcodeMap.hpp"

#include <iostream>
#include <iomanip>
#include <bitset>
#include <sstream>

constexpr uint16_t combineLittleEndian(uint8_t lowByte, uint8_t highByte) noexcept {
    return static_cast<uint16_t>(lowByte) | (static_cast<uint16_t>(highByte) << 8);
}

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
    // TODO delay based on how many cycles the instruction takes
    
    uint8_t opcode = 0x00;
    memory_.fetch(registers_.PC, opcode);

    auto it = opcodeMap.find(opcode);
    if (it == opcodeMap.end()) {
        //std::cerr << "Unknown opcode: " << std::hex << int(opcode) << "\n";
        registers_.PC++; // Increment PC if the opcode is unknown
        cycle_++;
        return;
    }

    currentInstruction_ = it->second.get();
    currentInstruction_->execute(this);
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
            memory_.fetch(registers_.PC, value);
            registers_.PC++;
            return false;
        case ZERO_PAGE:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            targetAddress = static_cast<uint16_t>(byte);
            memory_.fetch(targetAddress, value);
            return true;
        case ZERO_PAGE_X:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            byte += registers_.X; // Overflow expected
            targetAddress = static_cast<uint16_t>(byte);
            memory_.fetch(targetAddress, value);
            return true;
        case ZERO_PAGE_Y:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            byte += registers_.Y; // Overflow expected
            targetAddress = static_cast<uint16_t>(byte);
            memory_.fetch(targetAddress, value);
            return true;
        case RELATIVE: // Branch instructions
            memory_.fetch(registers_.PC, value);
            registers_.PC++;
            return false;
        case ABSOLUTE:
            memory_.fetch(registers_.PC, lowByte);
            registers_.PC++;
            memory_.fetch(registers_.PC, highByte);
            registers_.PC++;
            targetAddress = combineLittleEndian(lowByte, highByte);
            memory_.fetch(targetAddress, value);
            return true;
        case ABSOLUTE_X:
            memory_.fetch(registers_.PC, lowByte);
            registers_.PC++;
            memory_.fetch(registers_.PC, highByte);
            registers_.PC++;
            targetAddress = combineLittleEndian(lowByte, highByte);
            memory_.fetch(targetAddress + registers_.X, value);
            return true;
        case ABSOLUTE_Y:
            memory_.fetch(registers_.PC, lowByte);
            registers_.PC++;
            memory_.fetch(registers_.PC, highByte);
            registers_.PC++;
            targetAddress = combineLittleEndian(lowByte, highByte);;
            memory_.fetch(targetAddress + registers_.Y, value);
            return true;
        case INDIRECT:
            memory_.fetch(registers_.PC, lowByte);
            registers_.PC++;
            memory_.fetch(registers_.PC, highByte);
            registers_.PC++;
            targetAddress = combineLittleEndian(lowByte, highByte);
            registers_.PC = targetAddress;
            return false;
        case INDIRECT_X:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            byte += registers_.Y; // Overflow expected
            targetAddress = static_cast<uint16_t>(byte);
            memory_.fetch(targetAddress,     lowByte);
            memory_.fetch(targetAddress + 1, highByte);
            targetAddress = combineLittleEndian(lowByte, highByte);
            memory_.fetch(targetAddress, value);
            return true;
        case INDIRECT_Y:
            memory_.fetch(registers_.PC, byte);
            registers_.PC++;
            targetAddress = static_cast<uint16_t>(byte);
            memory_.fetch(targetAddress,     lowByte);
            memory_.fetch(targetAddress + 1, highByte);
            targetAddress = combineLittleEndian(lowByte, highByte) + registers_.Y;
            memory_.fetch(targetAddress, value);
            return true;
        default:
            std::cerr << "Addressing mode not implemented!" << std::endl;
            std::runtime_error("Addressing mode not implemented");
    }
}

void CPU::printStatus() const
{
    std::cout << "CPU Cycles: 0x" << cycle_ << "\n" << std::setfill('0') << std::uppercase
            << "PC: 0x" << std::setw(4)<< std::hex << static_cast<int>(registers_.PC) << "\n"
            << "SP: 0x" << std::setw(4)<< std::hex << static_cast<int>(registers_.SP) << "\n"
            << "A:  0x" << std::setw(2)<< std::hex << static_cast<int>(registers_.A)  << "\n"
            << "X:  0x" << std::setw(2)<< std::hex << static_cast<int>(registers_.X)  << "\n"
            << "Y:  0x" << std::setw(2)<< std::hex << static_cast<int>(registers_.Y)  << "\n"
            << "Status Register: 0b" << std::bitset<8>(registers_.P.reg) << std::endl;
}

std::string CPU::getRegisterStatusStr(bool renderVersion) const
{
    std::ostringstream out;

    if (renderVersion)
    {
        out << "STATUS: " << "\n";
    }
    else
    {
        out << "STATUS: " << std::bitset<8>(registers_.P.reg) << "\n";
    }
    
    out << std::setfill('0') << std::uppercase
        << "PC: $" << std::hex << std::setw(4) << static_cast<int>(registers_.PC) << "\n"
        << "SP: $" << std::hex << std::setw(4) << static_cast<int>(registers_.SP) << "\n"
        << "A:   0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(registers_.A) << std::dec << " - " << std::setw(3) << std::setfill(' ') << std::right << static_cast<int>(registers_.A) << "\n"
        << "X:   0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(registers_.X) << std::dec << " - " << std::setw(3) << std::setfill(' ') << std::right << static_cast<int>(registers_.X) << "\n"
        << "Y:   0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(registers_.Y) << std::dec << " - " << std::setw(3) << std::setfill(' ') << std::right << static_cast<int>(registers_.Y);

    return out.str();
}

std::string CPU::getRegisterStatusStr(uint8_t& statusRegister) const
{
    statusRegister = registers_.P.reg;
    return getRegisterStatusStr(true);
}

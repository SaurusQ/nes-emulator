
#include "Instruction.hpp"
#include "OpcodeMap.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>

Instruction::Instruction(uint8_t opcode, const char* name, AddressingMode mode, uint8_t bytes, uint8_t cycles)
    : Instruction::Instruction(opcode, name, mode, bytes, cycles, cycles)
{

}

Instruction::Instruction(uint8_t opcode, const char* name, AddressingMode mode, uint8_t bytes, uint8_t cycles, uint8_t cyclesPageCrossed)
    : opcode_(opcode), name_(name),mode_(mode), bytes_(bytes), cycles_(cycles), cyclesPageCrossed_(cyclesPageCrossed)
{

}

Instruction::~Instruction()
{

}

std::string Instruction::getInstructionListString(uint16_t address, const Memory& memory, unsigned int count)
{
    std::ostringstream oss;
    oss << std::hex << std::uppercase;

    uint8_t* memoryPtr = memory.getMemoryPtr();

    for (unsigned int instructionNum = 0; instructionNum < count; instructionNum++)
    {
        if (address > memory.size())
        {
            oss << "OVF";
            break;
        }
        uint8_t opcode = *(memoryPtr + address);

        auto it = opcodeMap.find(opcode);
        if (it == opcodeMap.end()) {
            oss << "$" << std::setw(4) << std::setfill('0') << address << " XXX\n";
            address++;
            continue;
        }
        Instruction* instruction = it->second.get();
        if (address + instruction->getLenght() > memory.size())
        {
            oss << "OVF";
            break;
        }
        oss << "$" << std::setw(4) << std::setfill('0') << address << " " << instruction->getStr(memoryPtr + address) << "\n";
        address += instruction->getLenght();

    }
    return oss.str();
}

std::string Instruction::getStr(uint8_t* memory)
{
    std::ostringstream oss;
    oss << std::hex << std::uppercase << name_;

    uint8_t* memoryPtr = memory + 1; // Skip opcode

    switch (mode_)
    {
        case AddressingMode::IMPLICIT:
            oss << " {IMP}";
            break;
        case AddressingMode::ACCUMULATOR:
            oss << " A {ACC}";
            break;
        case AddressingMode::IMMEDIATE:
            oss << " #" << std::setw(2) << std::setfill('0') << static_cast<int>(*(memoryPtr)) << " {IMM}";
            break;
        case AddressingMode::ZERO_PAGE:
            oss << " $" << std::setw(2) << std::setfill('0') << static_cast<int>(*(memoryPtr)) << " {ZP0}";
            break;
        case AddressingMode::ZERO_PAGE_X:
            oss << " $" << std::setw(2) << std::setfill('0') << static_cast<int>(*(memoryPtr)) << ", X {ZPX}";
            break;
        case AddressingMode::ZERO_PAGE_Y:
            oss << " $" << std::setw(2) << std::setfill('0') << static_cast<int>(*(memoryPtr)) << ", Y {ZPY}";
            break;
        case AddressingMode::RELATIVE:
            oss << " $" << std::setw(2) << std::setfill('0') << +static_cast<int8_t>(*(memoryPtr)) << " {REL}";
            break;
        case AddressingMode::ABSOLUTE:
            oss << " $" << std::setw(4) << std::setfill('0') << combineLittleEndian(*(memoryPtr), *(memoryPtr + 1)) << " {ABS}";
            break;
        case AddressingMode::ABSOLUTE_X:
            oss << " $" << std::setw(4) << std::setfill('0') << combineLittleEndian(*(memoryPtr), *(memoryPtr + 1)) << ", X {ABX}";
            break;
        case AddressingMode::ABSOLUTE_Y:
            oss << " $" << std::setw(4) << std::setfill('0') << combineLittleEndian(*(memoryPtr), *(memoryPtr + 1)) << ", Y {ABY}";
            break;
        case AddressingMode::INDIRECT:
            oss << " ($" << std::setw(4) << std::setfill('0') << combineLittleEndian(*(memoryPtr), *(memoryPtr + 1)) << ") {IND}";
            break;
        case AddressingMode::INDIRECT_X:
            oss << " ($" << std::setw(4) << std::setfill('0') << combineLittleEndian(*(memoryPtr), *(memoryPtr + 1)) << ", X) {INX}";
            break;
        case AddressingMode::INDIRECT_Y:
            oss << " ($" << std::setw(4) << std::setfill('0') << combineLittleEndian(*(memoryPtr), *(memoryPtr + 1)) << "), Y {INY}";
            break;
        default:
            oss << " {UNK}";
            break;
    }

    return oss.str();
}

void ADC::operation(CPU* cpu, uint8_t mem) const
{
    cpu->registers_.A += mem + cpu->registers_.P.C;
}

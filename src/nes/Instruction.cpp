
#include "Instruction.hpp"
#include "OpcodeTable.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>

std::string InstructionHelper::getInstructionListString(uint16_t address, const Memory& memory, unsigned int count)
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

        const InstructionInfo& instructionInfo = opcodeInfoTable[opcode];
        if (address + instructionInfo.bytes > memory.size())
        {
            oss << "OVF";
            break;
        }
        oss << "$" << std::setw(4) << std::setfill('0') << address << " " << getStr(instructionInfo, memoryPtr + address) << "\n";
        address += instructionInfo.bytes;
    }
    return oss.str();
}

std::string InstructionHelper::getStr(const InstructionInfo& info, uint8_t* memory)
{
    std::ostringstream oss;
    oss << std::hex << std::uppercase << info.name;

    uint8_t* memoryPtr = memory + 1; // Skip opcode

    switch (info.mode)
    {
        case AddressingMode::IMPLICIT:
        case AddressingMode::IMPLICIT_SKIP:
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
            oss << " $" << std::setw(4) << std::setfill('0') << make16(*(memoryPtr), *(memoryPtr + 1)) << " {ABS}";
            break;
        case AddressingMode::ABSOLUTE_X:
            oss << " $" << std::setw(4) << std::setfill('0') << make16(*(memoryPtr), *(memoryPtr + 1)) << ", X {ABX}";
            break;
        case AddressingMode::ABSOLUTE_Y:
            oss << " $" << std::setw(4) << std::setfill('0') << make16(*(memoryPtr), *(memoryPtr + 1)) << ", Y {ABY}";
            break;
        case AddressingMode::INDIRECT:
            oss << " ($" << std::setw(4) << std::setfill('0') << make16(*(memoryPtr), *(memoryPtr + 1)) << ") {IND}";
            break;
        case AddressingMode::INDIRECT_X:
            oss << " ($" << std::setw(4) << std::setfill('0') << make16(*(memoryPtr), *(memoryPtr + 1)) << ", X) {INX}";
            break;
        case AddressingMode::INDIRECT_Y:
            oss << " ($" << std::setw(4) << std::setfill('0') << make16(*(memoryPtr), *(memoryPtr + 1)) << "), Y {INY}";
            break;
        default:
            oss << " {UNK}";
            break;
    }

    return oss.str();
}

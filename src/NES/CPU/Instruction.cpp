
#include "Instruction.hpp"
#include "OpcodeTable.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

namespace CPU
{
    std::string InstructionHelper::getInstructionString(const InstructionInfo& info, uint16_t address, const Mapper& mapper)
    {
        std::ostringstream oss;
        if (std::strlen(info.name) == 3) oss << " ";
        oss << std::hex << std::uppercase << info.name;
        
        address += 1; // Skip opcode
        
        std::vector<uint8_t> bytes;
        for (int i = 0; i < info.bytes; i++)
        {
            uint8_t byte;
            mapper.read<AS::CPU>(address + i, byte); // TODO how the lookahead should be done? Limits=
            bytes.push_back(byte);
        }
        uint16_t twoBytes = 0;
        if (bytes.size() >= 2)
        {
            twoBytes = make16(bytes[0], bytes[1]);
        }
        
        switch (info.mode) // TODO needs also custom code per instruction
        {
            case AddressingMode::IMPLICIT:
            case AddressingMode::IMPLICIT_SKIP:
            break;
            case AddressingMode::ACCUMULATOR:
            break;
            case AddressingMode::IMMEDIATE:
            oss << " #$" << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[0]);
            break;
            case AddressingMode::ZERO_PAGE:
            break;
            case AddressingMode::ZERO_PAGE_X:
            break;
            case AddressingMode::ZERO_PAGE_Y:
            break;
            case AddressingMode::RELATIVE:
            oss << " $" << std::setw(4) << std::setfill('0') << static_cast<int>(twoBytes);
            break;
            case AddressingMode::ABSOLUTE:
            break;
            case AddressingMode::ABSOLUTE_X:
            break;
            case AddressingMode::ABSOLUTE_Y:
            break;
            case AddressingMode::INDIRECT:
            break;
            case AddressingMode::INDIRECT_X:
            break;
            case AddressingMode::INDIRECT_Y:
            break;
            default:
            oss << " UNK";
            break;
        }
        
        std::string s = oss.str();
        size_t pad = 33 - s.size();
        
        return s.append(pad, ' ');
    }

    std::string InstructionHelper::getInstructionListString(uint16_t address, const Mapper& mapper, unsigned int count)
    {
        std::ostringstream oss;
        oss << std::hex << std::uppercase;
        
        for (unsigned int instructionNum = 0; instructionNum < count; instructionNum++)
        {
            uint8_t opcode;
            mapper.read<AS::CPU>(address, opcode);
            
            const InstructionInfo& instructionInfo = opcodeInfoTable[opcode];
            oss << "$" << std::setw(4) << std::setfill('0') << address << " " << getStr(instructionInfo, mapper, address) << "\n";
            address += instructionInfo.bytes;
        }
        return oss.str();
    }

    std::string InstructionHelper::getStr(const InstructionInfo& info, const Mapper& mapper, uint16_t address)
    {
        std::ostringstream oss;
        oss << std::hex << std::uppercase << info.name;
        
        address++; // Skip opcode
        
        uint8_t lowByte;
        uint8_t highByte;
        mapper.read<AS::CPU>(address, lowByte);
        mapper.read<AS::CPU>(address + 1, highByte);

        uint16_t twoBytes = make16(lowByte, highByte);

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
            oss << " #" << std::setw(2) << std::setfill('0') << lowByte << " {IMM}";
            break;
            case AddressingMode::ZERO_PAGE:
            oss << " $" << std::setw(2) << std::setfill('0') << lowByte << " {ZP0}";
            break;
            case AddressingMode::ZERO_PAGE_X:
            oss << " $" << std::setw(2) << std::setfill('0') << lowByte << ", X {ZPX}";
            break;
            case AddressingMode::ZERO_PAGE_Y:
            oss << " $" << std::setw(2) << std::setfill('0') << lowByte << ", Y {ZPY}";
            break;
            case AddressingMode::RELATIVE:
            oss << " $" << std::setw(2) << std::setfill('0') << +static_cast<int8_t>(lowByte) << " {REL}";
            break;
            case AddressingMode::ABSOLUTE:
            oss << " $" << std::setw(4) << std::setfill('0') << twoBytes << " {ABS}";
            break;
            case AddressingMode::ABSOLUTE_X:
            oss << " $" << std::setw(4) << std::setfill('0') << twoBytes << ", X {ABX}";
            break;
            case AddressingMode::ABSOLUTE_Y:
            oss << " $" << std::setw(4) << std::setfill('0') << twoBytes << ", Y {ABY}";
            break;
            case AddressingMode::INDIRECT:
            oss << " ($" << std::setw(4) << std::setfill('0') << twoBytes << ") {IND}";
            break;
            case AddressingMode::INDIRECT_X:
            oss << " ($" << std::setw(4) << std::setfill('0') << twoBytes << ", X) {INX}";
            break;
            case AddressingMode::INDIRECT_Y:
            oss << " ($" << std::setw(4) << std::setfill('0') << twoBytes << "), Y {INY}";
            break;
            default:
            oss << " {UNK}";
            break;
        }
        
        return oss.str();
    }
}

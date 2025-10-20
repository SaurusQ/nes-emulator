#pragma once

#include "Instruction.hpp"

#include <map>
#include <cstdint>


const std::map<uint8_t, Instruction> opcodeMap = {
    // --- ADC ---
    {0x69, Instruction("ADC", 0x69, AddressingMode::IMMEDIATE,      2, 2,       Instruction::ADC)},
    {0x65, Instruction("ADC", 0x65, AddressingMode::ZERO_PAGE,      2, 3,       Instruction::ADC)},
    {0x75, Instruction("ADC", 0x75, AddressingMode::ZERO_PAGE_X,    2, 4,       Instruction::ADC)},
    {0x6D, Instruction("ADC", 0x6D, AddressingMode::ABSOLUTE,       3, 4,       Instruction::ADC)},
    {0x7D, Instruction("ADC", 0x7D, AddressingMode::ABSOLUTE_X,     3, 4, 5,    Instruction::ADC)},
    {0x79, Instruction("ADC", 0x79, AddressingMode::ABSOLUTE_Y,     3, 4, 5,    Instruction::ADC)},
    {0x61, Instruction("ADC", 0x61, AddressingMode::INDIRECT_X,     2, 6,       Instruction::ADC)},
    {0x71, Instruction("ADC", 0x71, AddressingMode::INDIRECT_Y,     2, 5, 6,    Instruction::ADC)},

};

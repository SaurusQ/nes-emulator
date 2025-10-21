#pragma once

#include "Instruction.hpp"

#include <map>
#include <cstdint>


std::map<uint8_t, std::unique_ptr<Instruction>> buildOpcodeMap() {
    std::map<uint8_t, std::unique_ptr<Instruction>> map;

    map.emplace(0x69, std::make_unique<ADC>(0x69, AddressingMode::IMMEDIATE,   2, 2));
    map.emplace(0x65, std::make_unique<ADC>(0x65, AddressingMode::ZERO_PAGE,   2, 3));
    map.emplace(0x75, std::make_unique<ADC>(0x75, AddressingMode::ZERO_PAGE_X, 2, 4));
    map.emplace(0x6D, std::make_unique<ADC>(0x6D, AddressingMode::ABSOLUTE,    3, 4));
    map.emplace(0x7D, std::make_unique<ADC>(0x7D, AddressingMode::ABSOLUTE_X,  3, 4, 5));
    map.emplace(0x79, std::make_unique<ADC>(0x79, AddressingMode::ABSOLUTE_Y,  3, 4, 5));
    map.emplace(0x61, std::make_unique<ADC>(0x61, AddressingMode::INDIRECT_X,  2, 6));
    map.emplace(0x71, std::make_unique<ADC>(0x71, AddressingMode::INDIRECT_Y,  2, 5, 6));
    
    return map;
}

const auto opcodeMap = buildOpcodeMap();
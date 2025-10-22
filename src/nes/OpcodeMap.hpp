#pragma once

#include "Instruction.hpp"
#include <map>
#include <cstdint>
#include <memory>

inline std::map<uint8_t, std::unique_ptr<Instruction>>& getOpcodeMap() {
    static std::map<uint8_t, std::unique_ptr<Instruction>> map;

    if (map.empty()) {
        map.emplace(0x69, std::make_unique<ADC>(0x69, "ADC", AddressingMode::IMMEDIATE, 2, 2));
        map.emplace(0x65, std::make_unique<ADC>(0x65, "ADC", AddressingMode::ZERO_PAGE, 2, 3));
        map.emplace(0x75, std::make_unique<ADC>(0x75, "ADC", AddressingMode::ZERO_PAGE_X, 2, 4));
        map.emplace(0x6D, std::make_unique<ADC>(0x6D, "ADC", AddressingMode::ABSOLUTE, 3, 4));
        map.emplace(0x7D, std::make_unique<ADC>(0x7D, "ADC", AddressingMode::ABSOLUTE_X, 3, 4, 5));
        map.emplace(0x79, std::make_unique<ADC>(0x79, "ADC", AddressingMode::ABSOLUTE_Y, 3, 4, 5));
        map.emplace(0x61, std::make_unique<ADC>(0x61, "ADC", AddressingMode::INDIRECT_X, 2, 6));
        map.emplace(0x71, std::make_unique<ADC>(0x71, "ADC", AddressingMode::INDIRECT_Y, 2, 5, 6));
    }

    return map;
}

inline auto& opcodeMap = getOpcodeMap();
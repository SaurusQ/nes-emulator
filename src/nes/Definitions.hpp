#pragma once

#include <cstdint>

enum AddressingMode
{
    IMPLICIT,
    ACCUMULATOR,
    IMMEDIATE,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    RELATIVE,
    ABSOLUTE,
    ABSOLUTE_X,
    ABSOLUTE_Y,
    INDIRECT,
    INDIRECT_X,
    INDIRECT_Y
};

constexpr uint16_t make16(uint8_t lowByte, uint8_t highByte) noexcept {
    return static_cast<uint16_t>(lowByte) | (static_cast<uint16_t>(highByte) << 8);
}

enum InstructionType
{
    ADC,
    AND,
    ASL,
    NOP
};

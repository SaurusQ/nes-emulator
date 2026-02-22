#pragma once

#include <cstdint>

constexpr uint16_t make16(uint8_t lowByte, uint8_t highByte) noexcept {
    return static_cast<uint16_t>(lowByte) | (static_cast<uint16_t>(highByte) << 8);
}

constexpr uint16_t spToAddr(uint8_t sp) noexcept {
    return static_cast<uint16_t>(0x0100 | sp);
}

constexpr uint8_t bAsHigh(uint8_t p) noexcept {
    return 0x10 | p;
}

constexpr uint8_t readStatusWithoutUB(uint8_t p, uint8_t res) noexcept {
    return (res & ~0x30) | (p & 0x30);
}

constexpr uint8_t getHighByte(uint16_t value) noexcept {
    return static_cast<uint8_t>(value >> 8);
}

constexpr uint8_t getLowByte(uint16_t value) noexcept {
    return static_cast<uint8_t>(value & 0x00FF);
}

enum AddressingMode
{
    IMPLICIT,
    IMPLICIT_SKIP, // Instructions that skip the next byte
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

enum InstructionType
{
    ADC,
    ALR,
    ANC,
    AND,
    ARR,
    AXS,
    ASL,
    BCC,
    BCS,
    BEQ,
    BIT,
    BMI,
    BNE,
    BPL,
    BRK,
    BVC,
    BVS,
    CLC,
    CLD,
    CLI,
    CLV,
    CMP,
    CPX,
    CPY,
    DCP,
    DEC,
    DEX,
    DEY,
    EOR,
    IGN,
    INC,
    INX,
    INY,
    ISC,
    JMP,
    JSR,
    LAX,
    LDA,
    LDX,
    LDY,
    LSR,
    NOP,
    ORA,
    PHA,
    PHP,
    PLA,
    PLP,
    RLA,
    RRA,
    ROL,
    ROR,
    RTI,
    RTS,
    SAX,
    SBC,
    SEC,
    SED,
    SEI,
    SKB,
    SLO,
    SRE,
    STA,
    STX,
    STY,
    TAX,
    TAY,
    TSX,
    TXA,
    TXS,
    TYA
};

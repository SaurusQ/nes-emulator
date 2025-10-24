
#include "OpcodeTable.hpp"

#include <map>
#include <cstdint>
#include <memory>

using AddressingMode = ::AddressingMode;
using InstructionType = ::InstructionType;

inline const std::array<InstructionData, 256>& getOpcodeTable() {
    static const std::array<InstructionData, 256> table = []() {
        std::array<InstructionData, 256> t{};

        t.fill(InstructionData{Instruction<NOP, IMPLICIT>::execute, 2});

        t[0x69] = {Instruction<ADC, IMMEDIATE>::execute,    2};
        t[0x65] = {Instruction<ADC, ZERO_PAGE>::execute,    3};
        t[0x75] = {Instruction<ADC, ZERO_PAGE_X>::execute,  4};
        t[0x6D] = {Instruction<ADC, ABSOLUTE>::execute,     4};
        t[0x7D] = {Instruction<ADC, ABSOLUTE_X>::execute,   4, 5};
        t[0x79] = {Instruction<ADC, ABSOLUTE_Y>::execute,   4, 5};
        t[0x61] = {Instruction<ADC, INDIRECT_X>::execute,   6};
        t[0x71] = {Instruction<ADC, INDIRECT_Y>::execute,   5, 6};

        t[0x29] = {Instruction<AND, IMMEDIATE>::execute,    2};
        t[0x25] = {Instruction<AND, ZERO_PAGE>::execute,    3};
        t[0x35] = {Instruction<AND, ZERO_PAGE_X>::execute,  4};
        t[0x2D] = {Instruction<AND, ABSOLUTE>::execute,     4};
        t[0x3D] = {Instruction<AND, ABSOLUTE_X>::execute,   4, 5};
        t[0x39] = {Instruction<AND, ABSOLUTE_Y>::execute,   4, 5};
        t[0x21] = {Instruction<AND, INDIRECT_X>::execute,   6};
        t[0x31] = {Instruction<AND, INDIRECT_Y>::execute,   5, 6};

        t[0x0A] = {Instruction<ASL, ACCUMULATOR>::execute,  2};
        t[0x06] = {Instruction<ASL, ZERO_PAGE>::execute,    5};
        t[0x16] = {Instruction<ASL, ZERO_PAGE_X>::execute,  6};
        t[0x0E] = {Instruction<ASL, ABSOLUTE>::execute,     6};
        t[0x1E] = {Instruction<ASL, ABSOLUTE_X>::execute,   7};

        t[0x90] = {Instruction<BCC, RELATIVE>::execute,     2, 4, 3};

        return t;
    }();

    return table;
}

inline const std::array<InstructionInfo, 256>& getOpcodeInfoTable() {
    static const std::array<InstructionInfo, 256> table = []() {
        std::array<InstructionInfo, 256> t{};

        t.fill(InstructionInfo{"UNK", IMPLICIT, 2});

        t[0x69] = {"ADC", IMMEDIATE,    2};
        t[0x65] = {"ADC", ZERO_PAGE,    2};
        t[0x75] = {"ADC", ZERO_PAGE_X,  2};
        t[0x6D] = {"ADC", ABSOLUTE,     3};
        t[0x7D] = {"ADC", ABSOLUTE_X,   3};
        t[0x79] = {"ADC", ABSOLUTE_Y,   3};
        t[0x61] = {"ADC", INDIRECT_X,   2};
        t[0x71] = {"ADC", INDIRECT_Y,   2};

        t[0x29] = {"AND", IMMEDIATE,    2};
        t[0x25] = {"AND", ZERO_PAGE,    2};
        t[0x35] = {"AND", ZERO_PAGE_X,  2};
        t[0x2D] = {"AND", ABSOLUTE,     3};
        t[0x3D] = {"AND", ABSOLUTE_X,   3};
        t[0x39] = {"AND", ABSOLUTE_Y,   3};
        t[0x21] = {"AND", INDIRECT_X,   2};
        t[0x31] = {"AND", INDIRECT_Y,   2};

        t[0x0A] = {"ASL", ACCUMULATOR,  1};
        t[0x06] = {"ASL", ZERO_PAGE,    2};
        t[0x16] = {"ASL", ZERO_PAGE_X,  2};
        t[0x0E] = {"ASL", ABSOLUTE,     3};
        t[0x1E] = {"ASL", ABSOLUTE_X,   3};

        t[0x90] = {"BCC", RELATIVE,     2};

        return t;
    }();

    return table;
}

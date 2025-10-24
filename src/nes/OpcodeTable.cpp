
#include "OpcodeTable.hpp"

#include <map>
#include <cstdint>
#include <memory>

using AddressingMode = ::AddressingMode;
using InstructionType = ::InstructionType;

const std::array<InstructionData, 256>& getOpcodeTable() {
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

        t[0xB0] = {Instruction<BCS, RELATIVE>::execute,     2, 4, 3};

        t[0xF0] = {Instruction<BEQ, RELATIVE>::execute,     2, 4, 3};

        t[0x24] = {Instruction<BIT, ZERO_PAGE>::execute,    3};
        t[0x2C] = {Instruction<BIT, ABSOLUTE>::execute,     4};

        t[0x30] = {Instruction<BMI, RELATIVE>::execute,     2, 4, 3};

        t[0xD0] = {Instruction<BNE, RELATIVE>::execute,     2, 4, 3};

        t[0x10] = {Instruction<BPL, RELATIVE>::execute,     2, 4, 3};

        t[0x00] = {Instruction<BRK, IMPLICIT_SKIP>::execute,7};

        t[0x50] = {Instruction<BVC, RELATIVE>::execute,     2, 4, 3};

        t[0x70] = {Instruction<BVS, RELATIVE>::execute,     2, 4, 3};

        t[0x18] = {Instruction<CLC, IMPLICIT>::execute,     2};
        t[0xD8] = {Instruction<CLD, IMPLICIT>::execute,     2};
        t[0x58] = {Instruction<CLI, IMPLICIT>::execute,     2};
        t[0xB8] = {Instruction<CLV, IMPLICIT>::execute,     2};

        t[0xC9] = {Instruction<CMP, IMMEDIATE>::execute,    2};
        t[0xC5] = {Instruction<CMP, ZERO_PAGE>::execute,    3};
        t[0xD5] = {Instruction<CMP, ZERO_PAGE_X>::execute,  4};
        t[0xCD] = {Instruction<CMP, ABSOLUTE>::execute,     4};
        t[0xDD] = {Instruction<CMP, ABSOLUTE_X>::execute,   4, 5};
        t[0xD9] = {Instruction<CMP, ABSOLUTE_Y>::execute,   4, 5};
        t[0xC1] = {Instruction<CMP, INDIRECT_X>::execute,   6};
        t[0xD1] = {Instruction<CMP, INDIRECT_Y>::execute,   5, 6};

        t[0xE0] = {Instruction<CPX, IMMEDIATE>::execute,    2};
        t[0xE4] = {Instruction<CPX, ZERO_PAGE>::execute,    3};
        t[0xEC] = {Instruction<CPX, ABSOLUTE>::execute,     4};

        t[0xC0] = {Instruction<CPY, IMMEDIATE>::execute,    2};
        t[0xC4] = {Instruction<CPY, ZERO_PAGE>::execute,    3};
        t[0xCC] = {Instruction<CPY, ABSOLUTE>::execute,     4};

        t[0xC6] = {Instruction<DEC, ZERO_PAGE>::execute,    5};
        t[0xD6] = {Instruction<DEC, ZERO_PAGE_X>::execute,  6};
        t[0xCE] = {Instruction<DEC, ABSOLUTE>::execute,     6};
        t[0xDE] = {Instruction<DEC, ABSOLUTE_X>::execute,   7};

        t[0xCA] = {Instruction<DEX, IMPLICIT>::execute,     2};
        t[0x88] = {Instruction<DEY, IMPLICIT>::execute,     2};

        t[0x49] = {Instruction<EOR, IMMEDIATE>::execute,    2};
        t[0x45] = {Instruction<EOR, ZERO_PAGE>::execute,    3};
        t[0x55] = {Instruction<EOR, ZERO_PAGE_X>::execute,  4};
        t[0x4D] = {Instruction<EOR, ABSOLUTE>::execute,     4};
        t[0x5D] = {Instruction<EOR, ABSOLUTE_X>::execute,   4, 5};
        t[0x59] = {Instruction<EOR, ABSOLUTE_Y>::execute,   4, 5};
        t[0x41] = {Instruction<EOR, INDIRECT_X>::execute,   6};
        t[0x51] = {Instruction<EOR, INDIRECT_Y>::execute,   5, 6};

        t[0xE6] = {Instruction<INC, ZERO_PAGE>::execute,    5};
        t[0xF6] = {Instruction<INC, ZERO_PAGE_X>::execute,  6};
        t[0xEE] = {Instruction<INC, ABSOLUTE>::execute,     6};
        t[0xFE] = {Instruction<INC, ABSOLUTE_X>::execute,   7};

        t[0xE8] = {Instruction<INX, IMPLICIT>::execute,     2};
        t[0xC8] = {Instruction<INY, IMPLICIT>::execute,     2};

        t[0x4C] = {Instruction<JMP, ABSOLUTE>::execute,     3};
        t[0x6C] = {Instruction<JMP, INDIRECT>::execute,     5};

        return t;
    }();

    return table;
}

const std::array<InstructionInfo, 256>& getOpcodeInfoTable() {
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

        t[0xB0] = {"BCS", RELATIVE,     2};

        t[0xF0] = {"BEQ", RELATIVE,     2};

        t[0x24] = {"BIT", ZERO_PAGE,    2};
        t[0x2C] = {"BIT", ABSOLUTE,     3};

        t[0x30] = {"BMI", RELATIVE,     2};

        t[0xD0] = {"BNE", RELATIVE,     2};

        t[0x10] = {"BPL", RELATIVE,     2};

        t[0x00] = {"BRK", IMPLICIT_SKIP,2};
        
        t[0x50] = {"BVC", RELATIVE,     2};

        t[0x70] = {"BVS", RELATIVE,     2};

        t[0x18] = {"CLC", IMPLICIT,     1};
        t[0xD8] = {"CLD", IMPLICIT,     1};
        t[0x58] = {"CLI", IMPLICIT,     1};
        t[0xB8] = {"CLV", IMPLICIT,     1};

        t[0xC9] = {"CMP", IMMEDIATE,    2};
        t[0xC5] = {"CMP", ZERO_PAGE,    2};
        t[0xD5] = {"CMP", ZERO_PAGE_X,  2};
        t[0xCD] = {"CMP", ABSOLUTE,     3};
        t[0xDD] = {"CMP", ABSOLUTE_X,   3};
        t[0xD9] = {"CMP", ABSOLUTE_Y,   3};
        t[0xC1] = {"CMP", INDIRECT_X,   2};
        t[0xD1] = {"CMP", INDIRECT_Y,   2};

        t[0xE0] = {"CPX", IMMEDIATE,    2};
        t[0xE4] = {"CPX", ZERO_PAGE,    2};
        t[0xEC] = {"CPX", ABSOLUTE,     3};

        t[0xC0] = {"CPY", IMMEDIATE,    2};
        t[0xC4] = {"CPY", ZERO_PAGE,    2};
        t[0xCC] = {"CPY", ABSOLUTE,     3};

        t[0xC6] = {"DEC", ZERO_PAGE,    2};
        t[0xD6] = {"DEC", ZERO_PAGE_X,  2};
        t[0xCE] = {"DEC", ABSOLUTE,     3};
        t[0xDE] = {"DEC", ABSOLUTE_X,   3};

        t[0xCA] = {"DEX", IMPLICIT,     1};
        t[0x88] = {"DEY", IMPLICIT,     1};

        t[0x49] = {"EOR", IMMEDIATE,    2};
        t[0x45] = {"EOR", ZERO_PAGE,    2};
        t[0x55] = {"EOR", ZERO_PAGE_X,  2};
        t[0x4D] = {"EOR", ABSOLUTE,     3};
        t[0x5D] = {"EOR", ABSOLUTE_X,   3};
        t[0x59] = {"EOR", ABSOLUTE_Y,   3};
        t[0x41] = {"EOR", INDIRECT_X,   2};
        t[0x51] = {"EOR", INDIRECT_Y,   2};

        t[0xE6] = {"INC", ZERO_PAGE,    2};
        t[0xF6] = {"INC", ZERO_PAGE_X,  2};
        t[0xEE] = {"INC", ABSOLUTE,     3};
        t[0xFE] = {"INC", ABSOLUTE_X,   3};

        t[0xE8] = {"INX", IMPLICIT,     1};
        t[0xC8] = {"INY", IMPLICIT,     1};

        t[0x4C] = {"JMP", ABSOLUTE,     3};
        t[0x6C] = {"JMP", INDIRECT,     3};

        return t;
    }();

    return table;
}

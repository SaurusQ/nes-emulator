
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

        t[0x20] = {Instruction<JSR, ABSOLUTE>::execute,     6};

        t[0xA9] = {Instruction<LDA, IMMEDIATE>::execute,    2};
        t[0xA5] = {Instruction<LDA, ZERO_PAGE>::execute,    3};
        t[0xB5] = {Instruction<LDA, ZERO_PAGE_X>::execute,  4};
        t[0xAD] = {Instruction<LDA, ABSOLUTE>::execute,     4};
        t[0xBD] = {Instruction<LDA, ABSOLUTE_X>::execute,   4, 5};
        t[0xB9] = {Instruction<LDA, ABSOLUTE_Y>::execute,   4, 5};
        t[0xA1] = {Instruction<LDA, INDIRECT_X>::execute,   6};
        t[0xB1] = {Instruction<LDA, INDIRECT_Y>::execute,   5, 6};

        t[0xA2] = {Instruction<LDX, IMMEDIATE>::execute,    2};
        t[0xA6] = {Instruction<LDX, ZERO_PAGE>::execute,    3};
        t[0xB6] = {Instruction<LDX, ZERO_PAGE_Y>::execute,  4};
        t[0xAE] = {Instruction<LDX, ABSOLUTE>::execute,     4};
        t[0xBE] = {Instruction<LDX, ABSOLUTE_Y>::execute,   4, 5};

        t[0xA0] = {Instruction<LDY, IMMEDIATE>::execute,    2};
        t[0xA4] = {Instruction<LDY, ZERO_PAGE>::execute,    3};
        t[0xB4] = {Instruction<LDY, ZERO_PAGE_X>::execute,  4};
        t[0xAC] = {Instruction<LDY, ABSOLUTE>::execute,     4};
        t[0xBC] = {Instruction<LDY, ABSOLUTE_X>::execute,   4, 5};

        t[0x4A] = {Instruction<LSR, ACCUMULATOR>::execute,  2};
        t[0x46] = {Instruction<LSR, ZERO_PAGE>::execute,    5};
        t[0x56] = {Instruction<LSR, ZERO_PAGE_X>::execute,  6};
        t[0x4E] = {Instruction<LSR, ABSOLUTE>::execute,     6};
        t[0x5E] = {Instruction<LSR, ABSOLUTE_X>::execute,   7};

        t[0xEA] = {Instruction<NOP, IMPLICIT>::execute,     2};

        t[0x09] = {Instruction<ORA, IMMEDIATE>::execute,    2};
        t[0x05] = {Instruction<ORA, ZERO_PAGE>::execute,    3};
        t[0x15] = {Instruction<ORA, ZERO_PAGE_X>::execute,  4};
        t[0x0D] = {Instruction<ORA, ABSOLUTE>::execute,     4};
        t[0x1D] = {Instruction<ORA, ABSOLUTE_X>::execute,   4, 5};
        t[0x19] = {Instruction<ORA, ABSOLUTE_Y>::execute,   4, 5};
        t[0x01] = {Instruction<ORA, INDIRECT_X>::execute,   6};
        t[0x11] = {Instruction<ORA, INDIRECT_Y>::execute,   5, 6};

        t[0x48] = {Instruction<PHA, IMPLICIT>::execute,     3};
        t[0x08] = {Instruction<PHP, IMPLICIT>::execute,     3};
        t[0x68] = {Instruction<PLA, IMPLICIT>::execute,     4};
        t[0x28] = {Instruction<PLP, IMPLICIT>::execute,     4};

        t[0x2A] = {Instruction<ROL, ACCUMULATOR>::execute,  2};
        t[0x26] = {Instruction<ROL, ZERO_PAGE>::execute,    5};
        t[0x36] = {Instruction<ROL, ZERO_PAGE_X>::execute,  6};
        t[0x2E] = {Instruction<ROL, ABSOLUTE>::execute,     6};
        t[0x3E] = {Instruction<ROL, ABSOLUTE_X>::execute,   7};

        t[0x6A] = {Instruction<ROR, ACCUMULATOR>::execute,  2};
        t[0x66] = {Instruction<ROR, ZERO_PAGE>::execute,    5};
        t[0x76] = {Instruction<ROR, ZERO_PAGE_X>::execute,  6};
        t[0x6E] = {Instruction<ROR, ABSOLUTE>::execute,     6};
        t[0x7E] = {Instruction<ROR, ABSOLUTE_X>::execute,   7};
        
        t[0x40] = {Instruction<RTI, IMPLICIT>::execute,     6};
        t[0x60] = {Instruction<RTS, IMPLICIT>::execute,     6};
        
        t[0xE9] = {Instruction<SBC, IMMEDIATE>::execute,    2};
        t[0xE5] = {Instruction<SBC, ZERO_PAGE>::execute,    3};
        t[0xF5] = {Instruction<SBC, ZERO_PAGE_X>::execute,  4};
        t[0xED] = {Instruction<SBC, ABSOLUTE>::execute,     4};
        t[0xFD] = {Instruction<SBC, ABSOLUTE_X>::execute,   4, 5};
        t[0xF9] = {Instruction<SBC, ABSOLUTE_Y>::execute,   4, 5};
        t[0xE1] = {Instruction<SBC, INDIRECT_X>::execute,   6};
        t[0xF1] = {Instruction<SBC, INDIRECT_Y>::execute,   5, 6};
        
        t[0x38] = {Instruction<SEC, IMPLICIT>::execute,     2};
        t[0xF8] = {Instruction<SED, IMPLICIT>::execute,     2};
        t[0x78] = {Instruction<SEI, IMPLICIT>::execute,     2};

        t[0x85] = {Instruction<STA, ZERO_PAGE>::execute,    3};
        t[0x95] = {Instruction<STA, ZERO_PAGE_X>::execute,  4};
        t[0x8D] = {Instruction<STA, ABSOLUTE>::execute,     4};
        t[0x9D] = {Instruction<STA, ABSOLUTE_X>::execute,   5};
        t[0x99] = {Instruction<STA, ABSOLUTE_Y>::execute,   5};
        t[0x81] = {Instruction<STA, INDIRECT_X>::execute,   6};
        t[0x91] = {Instruction<STA, INDIRECT_Y>::execute,   6};

        t[0x86] = {Instruction<STX, ZERO_PAGE>::execute,    3};
        t[0x96] = {Instruction<STX, ZERO_PAGE_Y>::execute,  4};
        t[0x8E] = {Instruction<STX, ABSOLUTE>::execute,     4};

        t[0x84] = {Instruction<STY, ZERO_PAGE>::execute,    3};
        t[0x94] = {Instruction<STY, ZERO_PAGE_X>::execute,  4};
        t[0x8C] = {Instruction<STY, ABSOLUTE>::execute,     4};

        t[0xAA] = {Instruction<TAX, IMPLICIT>::execute,     2};
        t[0xA8] = {Instruction<TAY, IMPLICIT>::execute,     2};
        t[0xBA] = {Instruction<TSX, IMPLICIT>::execute,     2};
        t[0x8A] = {Instruction<TXA, IMPLICIT>::execute,     2};
        t[0x9A] = {Instruction<TXS, IMPLICIT>::execute,     2};
        t[0x98] = {Instruction<TYA, IMPLICIT>::execute,     2};

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

        t[0x20] = {"JSR", ABSOLUTE,     3};

        t[0xA9] = {"LDA", IMMEDIATE,    2};
        t[0xA5] = {"LDA", ZERO_PAGE,    2};
        t[0xB5] = {"LDA", ZERO_PAGE_X,  2};
        t[0xAD] = {"LDA", ABSOLUTE,     3};
        t[0xBD] = {"LDA", ABSOLUTE_X,   3};
        t[0xB9] = {"LDA", ABSOLUTE_Y,   3};
        t[0xA1] = {"LDA", INDIRECT_X,   2};
        t[0xB1] = {"LDA", INDIRECT_Y,   2};

        t[0xA2] = {"LDX", IMMEDIATE,    2};
        t[0xA6] = {"LDX", ZERO_PAGE,    2};
        t[0xB6] = {"LDX", ZERO_PAGE_Y,  2};
        t[0xAE] = {"LDX", ABSOLUTE,     3};
        t[0xBE] = {"LDX", ABSOLUTE_Y,   3};

        t[0xA0] = {"LDY", IMMEDIATE,    2};
        t[0xA4] = {"LDY", ZERO_PAGE,    2};
        t[0xB4] = {"LDY", ZERO_PAGE_X,  2};
        t[0xAC] = {"LDY", ABSOLUTE,     3};
        t[0xBC] = {"LDY", ABSOLUTE_X,   3};

        t[0x4A] = {"LSR", ACCUMULATOR,  1};
        t[0x46] = {"LSR", ZERO_PAGE,    2};
        t[0x56] = {"LSR", ZERO_PAGE_X,  2};
        t[0x4E] = {"LSR", ABSOLUTE,     3};
        t[0x5E] = {"LSR", ABSOLUTE_X,   3};

        t[0xEA] = {"NOP", IMPLICIT,     1};

        t[0x09] = {"ORA", IMMEDIATE,    2};
        t[0x05] = {"ORA", ZERO_PAGE,    2};
        t[0x15] = {"ORA", ZERO_PAGE_X,  2};
        t[0x0D] = {"ORA", ABSOLUTE,     3};
        t[0x1D] = {"ORA", ABSOLUTE_X,   3};
        t[0x19] = {"ORA", ABSOLUTE_Y,   3};
        t[0x01] = {"ORA", INDIRECT_X,   2};
        t[0x11] = {"ORA", INDIRECT_Y,   2};

        t[0x48] = {"PHA", IMPLICIT,     1};
        t[0x08] = {"PHP", IMPLICIT,     1};
        t[0x68] = {"PLA", IMPLICIT,     1};
        t[0x28] = {"PLP", IMPLICIT,     1};

        t[0x2A] = {"ROL", ACCUMULATOR,  1};
        t[0x26] = {"ROL", ZERO_PAGE,    2};
        t[0x36] = {"ROL", ZERO_PAGE_X,  2};
        t[0x2E] = {"ROL", ABSOLUTE,     3};
        t[0x3E] = {"ROL", ABSOLUTE_X,   3};

        t[0x6A] = {"ROR", ACCUMULATOR,  1};
        t[0x66] = {"ROR", ZERO_PAGE,    2};
        t[0x76] = {"ROR", ZERO_PAGE_X,  2};
        t[0x6E] = {"ROR", ABSOLUTE,     3}; 
        t[0x7E] = {"ROR", ABSOLUTE_X,   3};

        t[0x40] = {"RTI", IMPLICIT,     1};
        t[0x60] = {"RTS", IMPLICIT,     1};

        t[0xE9] = {"SBC", IMMEDIATE,    2};
        t[0xE5] = {"SBC", ZERO_PAGE,    2};
        t[0xF5] = {"SBC", ZERO_PAGE_X,  2};
        t[0xED] = {"SBC", ABSOLUTE,     3};
        t[0xFD] = {"SBC", ABSOLUTE_X,   3};
        t[0xF9] = {"SBC", ABSOLUTE_Y,   3};
        t[0xE1] = {"SBC", INDIRECT_X,   2};
        t[0xF1] = {"SBC", INDIRECT_Y,   2};

        t[0x38] = {"SEC", IMPLICIT,     1};
        t[0xF8] = {"SED", IMPLICIT,     1};
        t[0x78] = {"SEI", IMPLICIT,     1};

        t[0x85] = {"STA", ZERO_PAGE,    2};
        t[0x95] = {"STA", ZERO_PAGE_X,  2};
        t[0x8D] = {"STA", ABSOLUTE,     3};
        t[0x9D] = {"STA", ABSOLUTE_X,   3};
        t[0x99] = {"STA", ABSOLUTE_Y,   3};
        t[0x81] = {"STA", INDIRECT_X,   2};
        t[0x91] = {"STA", INDIRECT_Y,   2};

        t[0x86] = {"STX", ZERO_PAGE,    2};
        t[0x96] = {"STX", ZERO_PAGE_Y,  2};
        t[0x8E] = {"STX", ABSOLUTE,     3};

        t[0x84] = {"STY", ZERO_PAGE,    2};
        t[0x94] = {"STY", ZERO_PAGE_X,  2};
        t[0x8C] = {"STY", ABSOLUTE,     3};

        t[0xAA] = {"TAX", IMPLICIT,     1};
        t[0xA8] = {"TAY", IMPLICIT,     1};
        t[0xBA] = {"TSX", IMPLICIT,     1};
        t[0x8A] = {"TXA", IMPLICIT,     1};
        t[0x9A] = {"TXS", IMPLICIT,     1};
        t[0x98] = {"TYA", IMPLICIT,     1};

        return t;
    }();

    return table;
}

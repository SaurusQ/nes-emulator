
#include "OpcodeMap.hpp"

#include <map>
#include <cstdint>
#include <memory>

inline const std::array<Instruction, 256>& getOpcodeMap() {
    static const std::array<Instruction, 256> table = []() {
        std::array<Instruction, 256> t{};

        t[0x69] = Instruction(0x69, "ADC", ADC, AddressingMode::IMMEDIATE,      2, 2);
        t[0x65] = Instruction(0x65, "ADC", ADC, AddressingMode::ZERO_PAGE,      2, 3);
        t[0x75] = Instruction(0x75, "ADC", ADC, AddressingMode::ZERO_PAGE_X,    2, 4);
        t[0x6D] = Instruction(0x6D, "ADC", ADC, AddressingMode::ABSOLUTE,       3, 4);
        t[0x7D] = Instruction(0x7D, "ADC", ADC, AddressingMode::ABSOLUTE_X,     3, 4, 5);
        t[0x79] = Instruction(0x79, "ADC", ADC, AddressingMode::ABSOLUTE_Y,     3, 4, 5);
        t[0x61] = Instruction(0x61, "ADC", ADC, AddressingMode::INDIRECT_X,     2, 6);
        t[0x71] = Instruction(0x71, "ADC", ADC, AddressingMode::INDIRECT_Y,     2, 5, 6);

        t[0x29] = Instruction(0x29, "AND", AND, AddressingMode::IMMEDIATE,      2, 2);
        t[0x25] = Instruction(0x25, "AND", AND, AddressingMode::ZERO_PAGE,      2, 3);
        t[0x35] = Instruction(0x35, "AND", AND, AddressingMode::ZERO_PAGE_X,    2, 4);
        t[0x2D] = Instruction(0x2D, "AND", AND, AddressingMode::ABSOLUTE,       3, 4);
        t[0x3D] = Instruction(0x3D, "AND", AND, AddressingMode::ABSOLUTE_X,     3, 4, 5);
        t[0x39] = Instruction(0x39, "AND", AND, AddressingMode::ABSOLUTE_Y,     3, 4, 5);
        t[0x21] = Instruction(0x21, "AND", AND, AddressingMode::INDIRECT_X,     2, 6);
        t[0x31] = Instruction(0x31, "AND", AND, AddressingMode::INDIRECT_Y,     2, 5, 6);

        return t;
    }();

    return table;
}

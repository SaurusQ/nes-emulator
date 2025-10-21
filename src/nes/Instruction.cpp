
#include "Instruction.hpp"

Instruction::Instruction(uint8_t opcode, AddressingMode mode, uint8_t bytes, uint8_t cycles)
    : Instruction::Instruction(opcode, mode, bytes, cycles, cycles)
{

}

Instruction::Instruction(uint8_t opcode, AddressingMode mode, uint8_t bytes, uint8_t cycles, uint8_t cyclesPageCrossed)
    : opcode_(opcode), mode_(mode), bytes_(bytes), cycles_(cycles), cyclesPageCrossed_(cyclesPageCrossed)
{

}

Instruction::~Instruction()
{

}

void ADC::operation(CPU* cpu, uint8_t mem) const
{
    cpu->registers_.A += mem + cpu->registers_.P.C;
}

std::string ADC::getStr() const
{
    return "ADC";
}

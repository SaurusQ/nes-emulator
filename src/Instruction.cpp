
#include "Instruction.hpp"

Instruction::Instruction(std::string name, uint8_t opcode, AddressingMode mode, uint8_t bytes, uint8_t cycles, OpcodeFunction method)
    : Instruction::Instruction(name, opcode, mode, bytes, cycles, cycles, method)
{

}

Instruction::Instruction(std::string name, uint8_t opcode, AddressingMode mode, uint8_t bytes, uint8_t cycles, uint8_t cyclesPageCrossed, OpcodeFunction method)
    : name_(name), opcode_(opcode), mode_(mode), bytes_(bytes), cycles_(cycles), cyclesPageCrossed_(cyclesPageCrossed), method_(method)
{

}

Instruction::~Instruction()
{

}

uint8_t Instruction::execute(CPU& cpu, Memory& memory)
{
    return method_(cpu, memory);
}

uint8_t Instruction::ADC(CPU& cpu, Memory& memory)
{
    uint8_t mem = 0x00;
    uint16_t targetAddress = 0x0000;
    bool pageCrossed = false;

    cpu.readData(mode_, targetAddress, mem, pageCrossed);
    cpu.registers_.A += mem + cpu.registers_.P.C;

    return pageCrossed ? cyclesPageCrossed_ : cycles_;
}
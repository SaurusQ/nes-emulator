
#include "CPU.hpp"

using InstructionType = ::InstructionType;

// --- Helper functions ---
inline void setZN(StatusRegister& reg, uint8_t value)
{
    reg.Z = value == 0;
    reg.N = (value & 0x80) != 0;
}


// --- Instructions ---
template <InstructionType IT, AddressingMode AM>
struct Operation
{
    inline static bool execute(CPU& cpu, uint8_t mem, uint16_t targetAddress)
    {
        switch (IT)
        {
            case ADC:
                {
                    uint8_t A = cpu.registers_.A;
                    cpu.registers_.P.C = __builtin_add_overflow(cpu.registers_.A, mem, &cpu.registers_.A);
                    cpu.registers_.P.V = ((cpu.registers_.A ^ A) & (cpu.registers_.A ^ mem) & 0x80);
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case AND:
                {
                    cpu.registers_.A &= mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case ASL:
                {
                    cpu.registers_.P.C = mem & 0x80;
                    mem <<= 1;
                    setZN(cpu.registers_.P, mem);
                    if (AM == ACCUMULATOR)
                    {
                        cpu.registers_.A = mem;
                    }
                    else
                    {
                        cpu.memory_.store(targetAddress, mem);
                    }
                    return false;
                }
            case BCC:
                {
                    if (!cpu.registers_.P.C)
                    {
                        cpu.registers_.PC += static_cast<int8_t>(mem);
                        return true;
                    }
                    return false;
                }
            case BCS:
                {
                    if (cpu.registers_.P.C)
                    {
                        cpu.registers_.PC += static_cast<int8_t>(mem);
                        return true;
                    }
                    return false;
                }
            case BEQ:
                {
                    if (cpu.registers_.P.Z)
                    {
                        cpu.registers_.PC += static_cast<int8_t>(mem);
                        return true;
                    }
                    return false;
                }
            case BIT:
                {
                    if (cpu.registers_.A & mem)
                    {
                        cpu.registers_.P.Z = cpu.registers_.A;
                        cpu.registers_.P.V = 0x40 & mem;
                        cpu.registers_.P.N = 0x80 & mem;
                    }
                    return false;
                }
            case BMI:
                {
                    if (cpu.registers_.P.N)
                    {
                        cpu.registers_.PC += static_cast<int8_t>(mem);
                        return true;
                    }
                    return false;
                }
            case BNE:
                {
                    if (!cpu.registers_.P.Z)
                    {
                        cpu.registers_.PC += static_cast<int8_t>(mem);
                        return true;
                    }
                    return false;
                }
            case BPL:
                {
                    if (!cpu.registers_.P.N)
                    {
                        cpu.registers_.PC += static_cast<int8_t>(mem);
                        return true;
                    }
                    return false;
                }
            case BRK:
                {
                    // TODO
                    return false;
                }
            case BVC:
                {
                    if (!cpu.registers_.P.V)
                    {
                        cpu.registers_.PC += static_cast<int8_t>(mem);
                        return true;
                    }
                    return false;
                }
            case BVS:
                {
                    if (cpu.registers_.P.V)
                    {
                        cpu.registers_.PC += static_cast<int8_t>(mem);
                        return true;
                    }
                    return false;
                }
            case CLC:
                {
                    cpu.registers_.P.C = 0x00;
                    return false;
                }
            case CLD:
                {
                    cpu.registers_.P.D = 0x00;
                    return false;
                }
            case CLI:
                {
                    cpu.registers_.P.I = 0x00;
                    return false;
                }
            case CLV:
                {
                    cpu.registers_.P.V = 0x00;
                    return false;
                }
            case CMP:
                {
                    uint8_t result = cpu.registers_.A - mem;
                    cpu.registers_.P.C = cpu.registers_.A >= mem;
                    setZN(cpu.registers_.P, result);
                    return false;
                }
            case CPX:
                {
                    uint8_t result = cpu.registers_.X - mem;
                    cpu.registers_.P.C = cpu.registers_.X >= mem;
                    setZN(cpu.registers_.P, result);
                    return false;
                }
            case CPY:
                {
                    uint8_t result = cpu.registers_.Y - mem;
                    cpu.registers_.P.C = cpu.registers_.Y >= mem;
                    setZN(cpu.registers_.P, result);
                    return false;
                }
            case DEC:
                {
                    mem -= 1;
                    cpu.memory_.store(targetAddress, mem);
                    setZN(cpu.registers_.P, mem);
                    return false;
                }
            case DEX:
                {
                    cpu.registers_.X -= 1;
                    setZN(cpu.registers_.P, cpu.registers_.X);
                    return false;
                }
            case DEY:
                {
                    cpu.registers_.Y -= 1;
                    setZN(cpu.registers_.P, cpu.registers_.Y);
                    return false;
                }
            case EOR:
                {
                    cpu.registers_.A ^= mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case INC:
                {
                    mem += 1;
                    cpu.memory_.store(targetAddress, mem);
                    setZN(cpu.registers_.P, mem);
                    return false;
                }
            case INX:
                {
                    cpu.registers_.X += 1;
                    setZN(cpu.registers_.P, cpu.registers_.X);
                    return false;
                }
            case INY:
                {
                    cpu.registers_.Y += 1;
                    setZN(cpu.registers_.P, cpu.registers_.Y);
                    return false;
                }
            case JMP:
                { // TODO it reads the next byte from the targetaddress, not correct of JMP
                    cpu.registers_.PC = targetAddress;
                    return false;
                }
            case JSR:
                {
                    // TODO
                    return false;
                }
            case LDA:
                {
                    cpu.registers_.A = mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case LDX:
                {
                    cpu.registers_.X = mem;
                    setZN(cpu.registers_.P, cpu.registers_.X);
                    return false;
                }
            case LDY:
                {
                    cpu.registers_.Y = mem;
                    setZN(cpu.registers_.P, cpu.registers_.Y);
                    return false;
                }
            case NOP:
                {
                    // Do nothing
                    return false;
                }
            case ORA:
                {
                    cpu.registers_.A |= mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case PHA:
                {
                    // TODO
                    return false;
                }
            case PHP:
                {
                    // TODO
                    return false;
                }
            case PLA:
                {
                    // TODO
                    return false;
                }
            case PLP:
                {
                    // TODO
                    return false;
                }
            case ROL:
                {
                    cpu.registers_.P.C = mem & 0x80;
                    mem <<= 1;
                    setZN(cpu.registers_.P, mem);
                    if (AM == ACCUMULATOR)
                    {
                        cpu.registers_.A = mem;
                    }
                    else
                    {
                        cpu.memory_.store(targetAddress, mem);
                    }
                    return false;
                }
            case ROR:
                {
                    cpu.registers_.P.C = mem & 0x01;
                    mem >>= 1;
                    setZN(cpu.registers_.P, mem);
                    if (AM == ACCUMULATOR)
                    {
                        cpu.registers_.A = mem;
                    }
                    else
                    {
                        cpu.memory_.store(targetAddress, mem);
                    }
                    return false;
                }
            case RTI:
                {
                    // TODO
                    return false;
                }
            case RTS:
                {
                    // TODO
                    return false;
                }
            case SBC:
                {
                    uint8_t A = cpu.registers_.A;
                    uint8_t subs = mem + !cpu.registers_.P.C;
                    cpu.registers_.P.C = (mem == 0xFF && !cpu.registers_.P.C) // Overflowed on the first phase
                        | __builtin_sub_overflow(cpu.registers_.A, subs, &cpu.registers_.A);

                    cpu.registers_.P.V = ((cpu.registers_.A ^ A) & (cpu.registers_.A ^ ~mem) & 0x80);
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case SEC:
                {
                    cpu.registers_.P.C = 0x01;
                    return false;
                }
            case SED:
                {
                    cpu.registers_.P.D = 0x01;
                    return false;
                }
            case SEI:
                {
                    cpu.registers_.P.I = 0x01;
                    return false;
                }
            case STA:
                {
                    cpu.memory_.store(targetAddress, cpu.registers_.A);
                    return false;
                }
            case STX:
                {
                    cpu.memory_.store(targetAddress, cpu.registers_.X);
                    return false;
                }
            case STY:
                {
                    cpu.memory_.store(targetAddress, cpu.registers_.Y);
                    return false;
                }
            case TAX:
                {
                    cpu.registers_.X = cpu.registers_.A;
                    setZN(cpu.registers_.P, cpu.registers_.X);
                    return false;
                }
            case TAY:
                {
                    cpu.registers_.Y = cpu.registers_.A;
                    setZN(cpu.registers_.P, cpu.registers_.Y);
                    return false;
                }
            case TSX:
                {
                    cpu.registers_.X = cpu.registers_.SP;
                    setZN(cpu.registers_.P, cpu.registers_.X);
                    return false;
                }
            case TXA:
                {
                    cpu.registers_.A = cpu.registers_.X;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case TXS:
                {
                    cpu.registers_.SP = cpu.registers_.X;
                    return false;
                }
            case TYA:
                {
                    cpu.registers_.A = cpu.registers_.Y;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            default:
                throw std::runtime_error("Operation not implemented");
        }
    }
};

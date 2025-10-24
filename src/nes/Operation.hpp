
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
            case NOP:
                {
                    // Do nothing
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
            default:
                throw std::runtime_error("Operation not implemented");
        }
    }
};

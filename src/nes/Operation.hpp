
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

            case NOP:
                {
                    // Do nothing
                    return false;
                }
    
            default:
                throw std::runtime_error("Operation not implemented");
                break;
        }
    }
};

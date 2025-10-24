
#include "CPU.hpp"

using InstructionType = ::InstructionType;

// --- Helper functions ---
inline void setZN(StatusRegister& reg, uint8_t value)
{
    reg.Z = value == 0;
    reg.N = (value & 0x80) != 0;
}


// --- Instructions ---
template <InstructionType IT>
struct Operation
{
    inline static void operation(CPU& cpu, uint8_t mem)
    {
        static_assert(IT != IT, "Operation not implemented for this InstructionType");
    }
};

template <>
struct Operation<ADC>
{
    inline static void operation(CPU& cpu, uint8_t mem)
    {
        uint8_t A = cpu.registers_.A;
        cpu.registers_.P.C = __builtin_add_overflow(cpu.registers_.A, mem, &cpu.registers_.A);
        cpu.registers_.P.V = ((cpu.registers_.A ^ A) & (cpu.registers_.A ^ mem) & 0x80);
        setZN(cpu.registers_.P, cpu.registers_.A);
    }
};

template <>
struct Operation<AND>
{
    inline static void operation(CPU& cpu, uint8_t mem)
    {
        cpu.registers_.A &= mem;
        setZN(cpu.registers_.P, cpu.registers_.A);
    }
};

template <>
struct Operation<ASL>
{
    inline static void operation(CPU& cpu, uint8_t mem)
    {
        (void)mem;
        cpu.registers_.P.C = cpu.registers_.A & 0x80;
        cpu.registers_.A <<= 1;
        setZN(cpu.registers_.P, cpu.registers_.A);
    }
};

template <>
struct Operation<NOP>
{
    inline static void operation(CPU& cpu, uint8_t mem)
    {
        // Do nothing
        (void)cpu;
        (void)mem;
    }
};

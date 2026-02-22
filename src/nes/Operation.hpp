
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
                    uint16_t sum = (uint16_t)cpu.registers_.A + (uint16_t)mem + (uint16_t)cpu.registers_.P.C;
                    cpu.registers_.A = sum & 0xFF;
                    cpu.registers_.P.C = sum > 0xFF;
                    cpu.registers_.P.V = ((cpu.registers_.A ^ A) & (cpu.registers_.A ^ mem) & 0x80);
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case ALR: // Unofficial
                {
                    cpu.registers_.A &= mem;
                    bool newCarry = mem & 0x01;
                    mem >>= 1;
                    cpu.registers_.P.C = newCarry;
                    cpu.registers_.A = mem;
                    setZN(cpu.registers_.P, mem);
                    return false;
                }
            case ANC: // Unofficial
                {
                    cpu.registers_.A &= mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    cpu.registers_.P.C = cpu.registers_.P.N;
                    return false;
                }
            case AND:
                {
                    cpu.registers_.A &= mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case ARR: // Unofficial
                {
                    cpu.registers_.A &= mem;
                    mem >>= 1;
                    mem |= cpu.registers_.P.C << 7;
                    cpu.registers_.A = mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    cpu.registers_.P.C = (mem >> 6) & 0x01;
                    uint8_t bit6 = (mem >> 6) & 0x01;
                    uint8_t bit5 = (mem >> 5) & 0x01;
                    cpu.registers_.P.V = bit6 ^ bit5;
                    return false;
                }
            case AXS: // Unofficial
                {
                    uint16_t res = cpu.registers_.A & cpu.registers_.X;
                    res = res - (uint16_t)mem;
                    cpu.registers_.X = static_cast<uint8_t>(res & 0xFF);
                    setZN(cpu.registers_.P, cpu.registers_.X);
                    cpu.registers_.P.C = (res >= mem);
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
                    cpu.registers_.P.Z = !(cpu.registers_.A & mem);
                    cpu.registers_.P.V = 0x40 & mem;
                    cpu.registers_.P.N = 0x80 & mem;
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
                    cpu.memory_.store(spToAddr(cpu.registers_.SP), getHighByte(cpu.registers_.PC));
                    cpu.registers_.SP--;
                    cpu.memory_.store(spToAddr(cpu.registers_.SP), getLowByte(cpu.registers_.PC));
                    cpu.registers_.SP--;
                    cpu.memory_.store(spToAddr(cpu.registers_.SP), cpu.registers_.P.reg);
                    cpu.registers_.SP--;
                    cpu.registers_.PC = 0xFFFE; // IRQ, interrupt request
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
            case CLI: // TODO IRQ
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
            case DCP: // Unofficial
                {
                    mem -= 1;
                    cpu.memory_.store(targetAddress, mem);
                    
                    uint8_t result = cpu.registers_.A - mem;
                    cpu.registers_.P.C = cpu.registers_.A >= mem;
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
            case ISC: // Unofficial
                {
                    mem += 1;
                    cpu.memory_.store(targetAddress, mem);
                    mem = ~mem;
                    uint8_t A = cpu.registers_.A;
                    uint16_t sum = (uint16_t)cpu.registers_.A + (uint16_t)mem + (uint16_t)cpu.registers_.P.C;
                    cpu.registers_.A = sum & 0xFF;
                    cpu.registers_.P.C = sum > 0xFF;
                    cpu.registers_.P.V = ((cpu.registers_.A ^ A) & (cpu.registers_.A ^ mem) & 0x80);
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case JMP:
                { // It reads the next byte from the targetaddress, not correct of JMP
                    cpu.registers_.PC = targetAddress;
                    return false;
                }
            case JSR:
                {
                    uint16_t returnAddress = cpu.registers_.PC - 1;
                    cpu.memory_.store(spToAddr(cpu.registers_.SP), getHighByte(returnAddress));
                    cpu.registers_.SP--;
                    cpu.memory_.store(spToAddr(cpu.registers_.SP), getLowByte(returnAddress));
                    cpu.registers_.SP--;
                    cpu.registers_.PC = targetAddress;
                    return false;
                }
            case LAX: // Unofficial
                {
                    cpu.registers_.A = mem;
                    cpu.registers_.X = cpu.registers_.A;
                    setZN(cpu.registers_.P, cpu.registers_.X);
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
            case LSR:
                {
                    bool newCarry = mem & 0x01;
                    mem >>= 1;
                    cpu.registers_.P.C = newCarry;

                    if (AM == ACCUMULATOR) cpu.registers_.A = mem;
                    else cpu.memory_.store(targetAddress, mem);

                    setZN(cpu.registers_.P, mem);
                    return false;
                }
            case SKB: // Unofficial
            case IGN: // Unofficial
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
                    cpu.memory_.store(spToAddr(cpu.registers_.SP), cpu.registers_.A);
                    cpu.registers_.SP--;
                    return false;
                }
            case PHP:
                {
                    cpu.memory_.store(spToAddr(cpu.registers_.SP), bAsHigh(cpu.registers_.P.reg));
                    cpu.registers_.SP--;
                    return false;
                }
            case PLA:
                {
                    cpu.registers_.SP++;
                    cpu.memory_.read(spToAddr(cpu.registers_.SP), cpu.registers_.A);
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case PLP: // TODO IRQ
                {
                    cpu.registers_.SP++;
                    uint8_t byte;
                    cpu.memory_.read(spToAddr(cpu.registers_.SP), byte);
                    cpu.registers_.P.reg = readStatusWithoutUB(cpu.registers_.P.reg, byte);
                    return false;
                }
            case RLA: // Unofficial
                {
                    bool newCarry = mem & 0x80;
                    mem <<= 1;
                    mem |= cpu.registers_.P.C;
                    cpu.registers_.P.C = newCarry;
                    
                    cpu.memory_.store(targetAddress, mem);

                    cpu.registers_.A &= mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case RRA: // Unofficial
                {
                    bool newCarry = mem & 0x01;
                    mem >>= 1;
                    mem |= cpu.registers_.P.C << 7;
                    cpu.registers_.P.C = newCarry;

                    cpu.memory_.store(targetAddress, mem);
                    
                    uint8_t A = cpu.registers_.A;
                    uint16_t sum = (uint16_t)cpu.registers_.A + (uint16_t)mem + (uint16_t)cpu.registers_.P.C;
                    cpu.registers_.A = sum & 0xFF;
                    cpu.registers_.P.C = sum > 0xFF;
                    cpu.registers_.P.V = ((cpu.registers_.A ^ A) & (cpu.registers_.A ^ mem) & 0x80);
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case ROL:
                {
                    bool newCarry = mem & 0x80;
                    mem <<= 1;
                    mem |= cpu.registers_.P.C;
                    cpu.registers_.P.C = newCarry;
                    
                    if (AM == ACCUMULATOR) cpu.registers_.A = mem;
                    else cpu.memory_.store(targetAddress, mem);

                    cpu.registers_.P.N = (mem & 0x80) != 0;
                    cpu.registers_.P.Z = cpu.registers_.A == 0;
                    return false;
                }
            case ROR:
                {
                    bool newCarry = mem & 0x01;
                    mem >>= 1;
                    mem |= cpu.registers_.P.C << 7;
                    cpu.registers_.P.C = newCarry;

                    if (AM == ACCUMULATOR) cpu.registers_.A = mem;
                    else cpu.memory_.store(targetAddress, mem);
                    
                    cpu.registers_.P.N = (mem & 0x80) != 0;
                    cpu.registers_.P.Z = cpu.registers_.A == 0;
                    return false;
                }
            case RTI:
                {
                    uint8_t byte, high, low;;
                    cpu.registers_.SP++;
                    cpu.memory_.read(spToAddr(cpu.registers_.SP), byte);
                    cpu.registers_.P.reg = readStatusWithoutUB(cpu.registers_.P.reg, byte);
                    cpu.registers_.SP++;
                    cpu.memory_.read(spToAddr(cpu.registers_.SP), low);
                    cpu.registers_.SP++;
                    cpu.memory_.read(spToAddr(cpu.registers_.SP), high);
                    cpu.registers_.PC = make16(low, high);
                    return false;
                }
            case RTS:
                {
                    uint8_t high, low;
                    cpu.registers_.SP++;
                    cpu.memory_.read(spToAddr(cpu.registers_.SP), low);
                    cpu.registers_.SP++;
                    cpu.memory_.read(spToAddr(cpu.registers_.SP), high);
                    cpu.registers_.PC = make16(low, high);
                    cpu.registers_.PC++;
                    return false;
                }
            case SAX: // Unofficial
                {
                    uint8_t byte = cpu.registers_.A & cpu.registers_.X;
                    cpu.memory_.store(targetAddress, byte);
                    return false;
                }
            case SBC:
                {
                    return Operation<ADC, AM>::execute(cpu, ~mem, targetAddress);
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
            case SEI: // TODO IRQ
                {
                    cpu.registers_.P.I = 0x01;
                    return false;
                }
            case SLO: // Unofficial
                {
                    cpu.registers_.P.C = mem & 0x80;
                    mem <<= 1;
                    cpu.memory_.store(targetAddress, mem);
                    cpu.registers_.A |= mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
                    return false;
                }
            case SRE: // Unofficial
                {
                    bool newCarry = mem & 0x01;
                    mem >>= 1;
                    cpu.registers_.P.C = newCarry;
                    cpu.memory_.store(targetAddress, mem);
                    cpu.registers_.A ^= mem;
                    setZN(cpu.registers_.P, cpu.registers_.A);
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
                std::string errorMsg = "Operation not implemented: ";
                errorMsg += "IT=" + std::to_string(static_cast<int>(IT));
                errorMsg += " AM=" + std::to_string(static_cast<int>(AM));
                errorMsg += " at PC=$" + std::to_string(cpu.registers_.PC);
                
                throw std::runtime_error(errorMsg);
        }
    }
};

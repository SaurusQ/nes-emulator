#pragma once

#include "Definitions.hpp"
#include "CPU.hpp"
#include "Memory.hpp"

#include <stdexcept>

using AddressingMode = ::AddressingMode;

template<AddressingMode AM>
struct MemoryAddressing
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t byte, low, high;
        switch (AM)
        {
            case IMPLICIT:
                return false;
            
            case IMPLICIT_SKIP:
                // Implicit addresses are considered to have 2-byte size
                cpu.registers_.PC++;
                return false;

            case ACCUMULATOR:
                pageCrossed = false;
                value = cpu.registers_.A;
                return false;

            case IMMEDIATE:
                cpu.memory_.read(cpu.registers_.PC, value);
                cpu.registers_.PC++;
                return false;

            case ZERO_PAGE:
                cpu.memory_.read(cpu.registers_.PC, byte);
                cpu.registers_.PC++;
                targetAddress = byte;
                cpu.memory_.read(targetAddress, value);
                return true;

            case ZERO_PAGE_X:
                cpu.memory_.read(cpu.registers_.PC, byte);
                cpu.registers_.PC++;
                byte += cpu.registers_.X; // Overflow expected
                targetAddress = byte;
                cpu.memory_.read(targetAddress, value);
                return true;

            case ZERO_PAGE_Y:
                cpu.memory_.read(cpu.registers_.PC, byte);
                cpu.registers_.PC++;
                byte += cpu.registers_.Y; // Overflow expected
                targetAddress = byte;
                cpu.memory_.read(targetAddress, value);
                return true;

            case RELATIVE:
                cpu.memory_.read(cpu.registers_.PC, value);
                cpu.registers_.PC++;
                return true;

            case ABSOLUTE:
                cpu.memory_.read(cpu.registers_.PC, low);
                cpu.registers_.PC++;
                cpu.memory_.read(cpu.registers_.PC, high);
                cpu.registers_.PC++;
                targetAddress = make16(low, high);
                cpu.memory_.read(targetAddress, value);
                return true;

            case ABSOLUTE_X:
                cpu.memory_.read(cpu.registers_.PC, low);
                cpu.registers_.PC++;
                cpu.memory_.read(cpu.registers_.PC, high);
                cpu.registers_.PC++;
                targetAddress = 0xFF & (make16(low, high) + cpu.registers_.X);
                cpu.memory_.read(targetAddress, value);
                return true;

            case ABSOLUTE_Y:
                cpu.memory_.read(cpu.registers_.PC, low);
                cpu.registers_.PC++;
                cpu.memory_.read(cpu.registers_.PC, high);
                cpu.registers_.PC++;
                targetAddress = 0xFF & (make16(low, high) + cpu.registers_.Y);
                cpu.memory_.read(targetAddress, value);
                return true;

            case INDIRECT: // Only JMP supports
                cpu.memory_.read(cpu.registers_.PC, low);
                cpu.registers_.PC++;
                cpu.memory_.read(cpu.registers_.PC, high);
                cpu.registers_.PC++;
                targetAddress = make16(low, high);
                cpu.memory_.read(targetAddress, low);
                cpu.memory_.read((targetAddress & 0xFF00) + ((targetAddress + 1) & 0x00FF), high);
                targetAddress = make16(low, high);
                return false;

            case INDIRECT_X:
                cpu.memory_.read(cpu.registers_.PC, byte);
                cpu.registers_.PC++;
                byte += cpu.registers_.X; // Overflow expected
                targetAddress = byte;
                cpu.memory_.read(targetAddress,              low);
                cpu.memory_.read((targetAddress + 1) & 0xFF, high);
                targetAddress = make16(low, high);
                cpu.memory_.read(targetAddress, value);
                return true;

            case INDIRECT_Y:
                cpu.memory_.read(cpu.registers_.PC, byte);
                cpu.registers_.PC++;
                targetAddress = byte;
                cpu.memory_.read(targetAddress,              low);
                cpu.memory_.read((targetAddress + 1) & 0xFF, high);
                targetAddress = make16(low, high) + cpu.registers_.Y;
                cpu.memory_.read(targetAddress, value);
                return true;

            default:
                throw std::runtime_error("Memory addressing not implemented");
                break;
        }
    }
};

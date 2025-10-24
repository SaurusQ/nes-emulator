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
        static_assert(AM != AM, "MemoryAddressing specialization not implemented for this mode");
        return false;
    }
    inline static bool write(CPU& cpu, uint16_t& targetAddress, uint8_t value)
    {
        cpu.memory_.store(targetAddress, value);
        return false;
    }
};

template <>
struct MemoryAddressing<IMPLICIT>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        (void)cpu;
        (void)targetAddress;
        (void)value;
        (void)pageCrossed;

        return false;
    }
    inline static bool write(CPU& cpu, uint16_t& targetAddress, uint8_t value)
    {
        (void)cpu;
        (void)targetAddress;
        (void)value;

        return false;
    }
};

template<>
struct MemoryAddressing<ACCUMULATOR>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        (void)targetAddress;
        (void)value;
        pageCrossed = false;
        value = cpu.registers_.A;
        return false;
    }
    inline static bool write(CPU& cpu, uint16_t& targetAddress, uint8_t value)
    {
        (void)targetAddress;
        cpu.registers_.A = value;
        return false;
    }
};

template<>
struct MemoryAddressing<IMMEDIATE>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        (void)targetAddress;
        cpu.memory_.read(cpu.registers_.PC, value);
        cpu.registers_.PC++;
        return false;
    }
};

template<>
struct MemoryAddressing<ZERO_PAGE>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t byte;
        cpu.memory_.read(cpu.registers_.PC, byte);
        cpu.registers_.PC++;
        targetAddress = byte;
        cpu.memory_.read(targetAddress, value);
        return true;
    }
};

template<>
struct MemoryAddressing<ZERO_PAGE_X>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t byte;
        cpu.memory_.read(cpu.registers_.PC, byte);
        cpu.registers_.PC++;
        byte += cpu.registers_.X; // Overflow expected
        targetAddress = byte;
        cpu.memory_.read(targetAddress, value);
        return true;
    }
};

template<>
struct MemoryAddressing<ZERO_PAGE_Y>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t byte;
        cpu.memory_.read(cpu.registers_.PC, byte);
        cpu.registers_.PC++;
        byte += cpu.registers_.Y; // Overflow expected
        targetAddress = byte;
        cpu.memory_.read(targetAddress, value);
        return true;
    }
};

template<>
struct MemoryAddressing<RELATIVE>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        cpu.memory_.read(cpu.registers_.PC, value);
        cpu.registers_.PC++;
        return true;
    }
};

template<>
struct MemoryAddressing<ABSOLUTE>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t low, high;
        cpu.memory_.read(cpu.registers_.PC, low);
        cpu.registers_.PC++;
        cpu.memory_.read(cpu.registers_.PC, high);
        cpu.registers_.PC++;
        targetAddress = make16(low, high);
        cpu.memory_.read(targetAddress, value);
        return true;
    }
};

template<>
struct MemoryAddressing<ABSOLUTE_X>
{
    static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t low, high;
        cpu.memory_.read(cpu.registers_.PC, low);
        cpu.registers_.PC++;
        cpu.memory_.read(cpu.registers_.PC, high);
        cpu.registers_.PC++;
        targetAddress = 0xFF & (make16(low, high) + cpu.registers_.X);
        cpu.memory_.read(targetAddress, value);
        return true;
    }
};

template<>
struct MemoryAddressing<ABSOLUTE_Y>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t low, high;
        cpu.memory_.read(cpu.registers_.PC, low);
        cpu.registers_.PC++;
        cpu.memory_.read(cpu.registers_.PC, high);
        cpu.registers_.PC++;
        targetAddress = 0xFF & (make16(low, high) + cpu.registers_.Y);
        cpu.memory_.read(targetAddress, value);
        return true;
    }
};

template<>
struct MemoryAddressing<INDIRECT>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t low, high;
        cpu.memory_.read(cpu.registers_.PC, low);
        cpu.registers_.PC++;
        cpu.memory_.read(cpu.registers_.PC, high);
        cpu.registers_.PC++;
        targetAddress = make16(low, high);
        cpu.registers_.PC = targetAddress;
        return false;
    }
};

template<>
struct MemoryAddressing<INDIRECT_X>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t byte, low, high;
            cpu.memory_.read(cpu.registers_.PC, byte);
            cpu.registers_.PC++;
            byte += cpu.registers_.Y; // Overflow expected
            targetAddress = byte;
            cpu.memory_.read(targetAddress,     low);
            cpu.memory_.read(targetAddress + 1, high);
            targetAddress = make16(low, high);
            cpu.memory_.read(targetAddress, value);
            return true;
    }
};

template<>
struct MemoryAddressing<INDIRECT_Y>
{
    inline static bool fetch(CPU& cpu, uint16_t& targetAddress, uint8_t& value, bool& pageCrossed)
    {
        uint8_t byte, low, high;
        cpu.memory_.read(cpu.registers_.PC, byte);
        cpu.registers_.PC++;
        targetAddress = byte;
        cpu.memory_.read(targetAddress,     low);
        cpu.memory_.read(targetAddress + 1, high);
        targetAddress = make16(low, high) + cpu.registers_.Y;
        cpu.memory_.read(targetAddress, value);
        return true;
    }
};

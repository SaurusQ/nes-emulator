#pragma once

#include "Definitions.hpp"
#include "CPU.hpp"
#include "Memory.hpp"
#include "Operation.hpp"
#include "MemoryAddressing.hpp"

#include <string>

struct InstructionData;

using ExecuteFunc = uint8_t (*)(CPU&, const InstructionData&);
using OperationFunc = void (*)(CPU&, uint8_t);

struct InstructionData
{
    InstructionData() = default;
    InstructionData(ExecuteFunc execute, uint8_t cycles)
        : execute(execute), cycles(cycles), cyclesPageCrossed(cycles), cyclesBranched(cycles) {}
    InstructionData(ExecuteFunc execute, uint8_t cycles, uint8_t cyclesPageCrossed)
        : execute(execute), cycles(cycles), cyclesPageCrossed(cyclesPageCrossed), cyclesBranched(cycles) {}
    InstructionData(ExecuteFunc execute, uint8_t cycles, uint8_t cyclesPageCrossed, uint8_t cyclesBranched)
        : execute(execute), cycles(cycles), cyclesPageCrossed(cyclesPageCrossed), cyclesBranched(cyclesBranched) {}
    
    ExecuteFunc     execute;
    uint8_t         cycles;
    uint8_t         cyclesPageCrossed;
    uint8_t         cyclesBranched;
};

struct InstructionInfo
{
    const char* name;
    AddressingMode mode;
    uint8_t bytes;
};

template <InstructionType IT, AddressingMode AM>
class Instruction
{
    public:
        inline static uint8_t execute(CPU& cpu, const InstructionData& data)
        {
            uint8_t mem = 0x00;
            uint16_t targetAddress = 0x0000;
            bool pageCrossed = false;

            MemoryAddressing<AM>::fetch(cpu, targetAddress, mem, pageCrossed);

            if (Operation<IT, AM>::execute(cpu, mem, targetAddress))
            {
                return data.cyclesBranched;
            }

            return pageCrossed ? data.cyclesPageCrossed : data.cycles;
        }
};

class InstructionHelper
{
    public:
        static std::string getInstructionString(const InstructionInfo& info, uint16_t address, const Memory& memory);
        static std::string getInstructionListString(uint16_t address, const Memory& memory, unsigned int count);
        static std::string getStr(const InstructionInfo& info, uint8_t* memory);
};


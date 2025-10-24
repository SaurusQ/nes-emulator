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
        : execute(execute), cycles(cycles), cyclesPageCrossed(cycles) {}
    InstructionData(ExecuteFunc execute, uint8_t cycles, uint8_t cyclesPageCrossed)
        : execute(execute), cycles(cycles), cyclesPageCrossed(cyclesPageCrossed) {}

    ExecuteFunc     execute;
    uint8_t         cycles;
    uint8_t         cyclesPageCrossed;
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
        inline static uint8_t execute(CPU& cpu, const InstructionData& data) {
            uint8_t mem = 0x00;
            uint8_t value = 0x00;
            uint16_t targetAddress = 0x0000;
            bool pageCrossed = false;

            MemoryAddressing<AM>::fetch(cpu, targetAddress, value, pageCrossed);
            Operation<IT>::operation(cpu, mem);

            return pageCrossed ? data.cyclesPageCrossed : data.cycles;
        }
};

class InstructionHelper
{
    public:
        virtual ~InstructionHelper() = default;

        static std::string getStr(const InstructionInfo& info, uint8_t* memory);

        static std::string getInstructionListString(uint16_t address, const Memory& memory, unsigned int count);

};


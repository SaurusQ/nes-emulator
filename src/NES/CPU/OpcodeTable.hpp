#pragma once

#include "Instruction.hpp"

#include <cstdint>
#include <memory>
#include <array>

namespace CPU
{
    const std::array<InstructionData, 256>& getOpcodeTable();
    inline const auto& opcodeTable = getOpcodeTable();
    
    const std::array<InstructionInfo, 256>& getOpcodeInfoTable();
    inline const auto& opcodeInfoTable = getOpcodeInfoTable();
}

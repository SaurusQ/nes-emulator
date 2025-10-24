#pragma once

#include "Instruction.hpp"

#include <cstdint>
#include <memory>
#include <array>

inline const std::array<Instruction, 256>& getOpcodeMap();
inline auto& opcodeMap = getOpcodeMap();

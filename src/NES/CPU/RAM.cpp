#include "Memory.hpp"

#include <memory>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>


namespace CPU
{
    std::string RAM::getMemoryRegionStr(uint16_t address, size_t size) const
    {
        std::ostringstream oss;
        oss << std::hex << std::uppercase;
        std::string start = "";
        for (size_t i = 0; i < size && address + i < NES_CPU_RAM_SIZE; i++)
        {
            if (i % 8 == 0)
            {
                oss << start << "$" << std::setw(4) << std::setfill('0') << address + i;
                start = "\n";
            }
            oss << " " << std::setw(2) << std::setfill('0') << static_cast<int>(memory_[address + i]);
        }
        return oss.str();
    }
}

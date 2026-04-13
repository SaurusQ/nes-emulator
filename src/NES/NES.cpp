
#include "NES.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

NES::NES() : cpu_(memory_)
{

}

NES::~NES()
{
}

void NES::powerOn()
{
}

void NES::reset()
{
    cpu_.resetRegisters();
}

void NES::runCycle()
{
    cpu_.clockTick();
}

void NES::loadDotNESDirectToMemory(const char* filename)
{
    std::ifstream file = std::ifstream(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return;
    }

    std::vector<uint8_t> programData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    if (programData.size() < 16)
    {
        std::cerr << "Error: file too small" << std::endl;
        return;
    }

    uint16_t PRG_ROM_SIZE = programData[4] * 0x4000;
    uint16_t CHR_ROM_SIZE = programData[5] * 0x2000;

    std::cout << "PRG_ROM_SIZE: 0x" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(PRG_ROM_SIZE) << "\n"
              << "CHR_ROM_SIZE: 0x" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(CHR_ROM_SIZE) << "\n";

    std::vector<uint8_t> programDataWithoutHeader(programData.begin() + 16, programData.end());

    memory_.loadData(0xC000, programDataWithoutHeader.data(), PRG_ROM_SIZE);    
    
}

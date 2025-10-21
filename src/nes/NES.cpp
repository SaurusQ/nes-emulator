
#include "NES.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

NES::NES() : cpu_(memory_)
{
    std::string fileName = "program.bin";
    std::ifstream file = std::ifstream(fileName, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file " << fileName << std::endl;
        return;
    }

    std::vector<uint8_t> programData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    memory_.loadData(0x0000, programData.data(), programData.size());
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
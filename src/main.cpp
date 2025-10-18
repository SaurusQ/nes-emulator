
#include "CPU.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>

int main()
{
    Memory memory;
    CPU cpu(memory);

    // Read binary file
    std::string fileName = "program.bin";
    std::ifstream file = std::ifstream(fileName, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file " << fileName << std::endl;
        return -1;
    }

    std::vector<uint8_t> programData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    memory.loadData(0x0000, programData.data(), programData.size());

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        cpu.clockTick();
        cpu.printStatus();
    }

    return 0;
}

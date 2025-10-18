
#include "CPU.hpp"

#include <iostream>

int main()
{
    CPU cpu;

    while (true) {
        cpu.clockTick();
        cpu.printStatus();
    }

    return 0;
}
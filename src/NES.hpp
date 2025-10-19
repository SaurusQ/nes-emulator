#pragma once

#include "CPU.hpp"
#include "Memory.hpp"

class NES
{
    public:   
        NES();
        ~NES();

        void powerOn();
        void reset();
        void runCycle();

    private:

        Memory memory_;
        CPU cpu_;    
};

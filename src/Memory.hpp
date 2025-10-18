#pragma once

#include "Definitions.hpp"

#include <memory>


class Memory
{
    public:
        Memory();
        ~Memory();
        
        void fetch(uint16_t address, uint8_t& data) const;
        void store(uint16_t address, uint8_t data);

    private:
        std::unique_ptr<uint8_t[]> memory_;

};
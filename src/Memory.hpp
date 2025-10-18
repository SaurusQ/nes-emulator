#pragma once

#include "Definitions.hpp"

#include <memory>


class Memory
{
    public:
        Memory();
        ~Memory();
        
        void configureRegion(uint16_t startAddress, uint16_t size, uint8_t* data);

        void fetch(uint16_t address, uint8_t& data) const;
        void store(uint16_t address, uint8_t data);

    private:
        std::unique_ptr<uint8_t[]> memory_;

};
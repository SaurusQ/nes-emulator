#pragma once

#include <cstdint>

class BusDevice
{
    public:
        BusDevice(uint16_t addressLow, uint16_t addressHigh) : addressLow_(addressLow), addressHigh_(addressHigh) {}
        virtual ~BusDevice() = default;

        virtual void read(uint16_t address, uint8_t& data) = 0;
        virtual void store(uint16_t address, uint8_t data) = 0;

        uint16_t start() const { return addressLow_; }
        uint16_t end()   const { return addressHigh_; }

    private:
        uint16_t addressLow_;
        uint16_t addressHigh_;
};

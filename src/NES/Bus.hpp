#pragma once

#include "BusDevice.hpp"

#include <cstdint>
#include <vector>
#include <functional>

class Bus
{
    public:
        Bus() = default;
        ~Bus() = default;

        void read(uint16_t address, uint8_t& data)
        {
            readTable_[address](address,data);
        }

        void store(uint16_t address, uint8_t data)
        {
            storeTable_[address](address, data);
        }

        void attach(BusDevice* device)
        {
            for (uint32_t addr = device->start(); addr <= device->end(); ++addr) {
                readTable_[addr] = &BusDevice::read;
                storeTable_[addr] = &BusDevice::store;
            }
        }

    private:

        std::vector<std::function<void(uint16_t, uint8_t&)>> storeTable_;
        std::vector<std::function<void(uint16_t, uint8_t)>>  readTable_;

        uint8_t lastRead_ = 0x00;
};

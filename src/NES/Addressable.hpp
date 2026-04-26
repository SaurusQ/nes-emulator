#pragma once

#include <cstdint>
#include <string>

class Addressable
{
    public:
        Addressable() = default;
        virtual ~Addressable() = default;

        virtual void read(uint16_t address, uint8_t& data) const;
        virtual void store(uint16_t address, uint8_t data);
        virtual size_t size() const;

        virtual std::string getMemoryRegionStr(uint16_t address, size_t size) const;
        virtual uint8_t* getMemoryPtr() const;
};

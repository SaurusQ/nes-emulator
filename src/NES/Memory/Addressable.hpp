#pragma once

#include <cstdint>
#include <string>
#include <sstream>

class Addressable
{
    public:
        Addressable() = default;
        virtual ~Addressable() = default;

        virtual void read(uint16_t address, uint8_t& data) const { data = this->getMemoryPtr()[address]; }
        virtual void store(uint16_t address, uint8_t data) { this->getMemoryPtr()[address] = data; }
        virtual size_t size() const;
        virtual inline const uint8_t* getMemoryPtr() const { return this->getMemoryPtr(); }
        std::string getMemoryRegionStr(uint16_t address, size_t size) const
        {
            std::ostringstream oss;
            oss << std::hex << std::uppercase;
            std::string start = "";
            const uint8_t* memory = this->getMemoryPtr();
            for (size_t i = 0; i < size && address + i < this->size(); i++)
            {
                if (i % 8 == 0)
                {
                    oss << start << "$" << std::setw(4) << std::setfill('0') << address + i;
                    start = "\n";
                }
                oss << " " << std::setw(2) << std::setfill('0') << static_cast<const int>(memory[address + i]);
            }
            return oss.str();
        }
    protected:
        virtual inline uint8_t* getMemoryPtr();
};

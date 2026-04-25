#pragma once

#include <cstdint>
#include <memory>

namespace PPU
{
    class VRAM
    {
        public:
            VRAM();
            ~VRAM() = default;

            void read(uint16_t address, uint8_t& data) const;
            void store(uint16_t address, uint8_t data);
            
            uint8_t* getMemoryPtr() const { return vram_.get(); }
        private:
            std::unique_ptr<uint8_t[]> vram_;
    };
}
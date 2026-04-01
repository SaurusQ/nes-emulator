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
                
        private:
            std::unique_ptr<uint8_t[]> vram_;
    };
}
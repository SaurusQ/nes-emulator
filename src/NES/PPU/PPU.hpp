#pragma once

#include "Registers.hpp"
#include "Definitions.hpp"
#include "VRAM.hpp"
#include "../Mappers/Mapper.hpp"
#include "../Memory/Addressable.hpp"

#include <cstdint>
#include <vector>

namespace PPU
{
    class PPU : public Addressable
    {
        public:
            PPU(Mapper& mapper);
            ~PPU() = default;

            void reset();
            void tick();

            void copyScreenBuffer(std::vector<Pixel>& dst) const { dst = screenBuffer_; }
            std::vector<Pixel> getScreenBuffer() const { return screenBuffer_; }

            const uint8_t* getPatternTableAddress() const { return vram_.getMemoryPtr(); }
        
            // Addressable
            size_t size() const { return 8; }
        protected:
            inline uint8_t* getMemoryPtr() { reinterpret_cast<const uint8_t*>(&reg_); }
        private:
            uint16_t getBaseNameTableAddress();
            uint16_t getSpritePatternTableAddress();
    
            Mapper& mapper_;
            Registers reg_;
            uint64_t cycle_ = 0;
            uint16_t dot_ = 0;
            std::vector<Pixel> screenBuffer_;

            VRAM vram_;
    };
}

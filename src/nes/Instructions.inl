
// --- Helper functions ---
inline void setZN(StatusRegister& reg, uint8_t value)
{
    reg.Z = value == 0;
    reg.N = (value & 0x80) != 0;
}


// --- Instructions ---
inline void ADC(Registers* reg, uint8_t mem)
{
    uint8_t A = reg->A;
    reg->P.C = __builtin_add_overflow(reg->A, mem, &reg->A);
    reg->P.V = ((reg->A ^ A) & (reg->A ^ mem) & 0x80);
    setZN(reg->P, reg->A);
}

inline void AND(Registers* reg, uint8_t mem)
{
    reg->A &= mem;
    setZN(reg->P, reg->A);
}

inline void NOP(Registers* reg, uint8_t mem)
{
    // Do nothing
}

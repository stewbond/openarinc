#include "a429dis.hpp"

namespace a429
{
    UINT a429dis::operator= (UINT word)
    {
        *m_packed = word;
        return *m_packed;
    }

    a429dis& a429dis::SetBit(bool value, int pos)
    {
        if (value)
            *m_packed |=   0x1 << (pos - 1);
        else
            *m_packed &= ~(0x1 << (pos - 1));
        return *this;
    }

    a429dis& a429dis::SetBits(UINT value, int msb, int lsb)
    {
        UINT mask = ~(-1 << msb) & (-1 << (lsb-1));
        *m_packed &= ~mask;
        *m_packed |= (value << (lsb-1)) & mask;
        return *this;
    }

    bool a429dis::GetBit(int pos) const
    {
        return ((*m_packed >> (pos - 1)) & 0x1);
    }


    UINT a429dis::GetBits(int msb, int lsb) const
    {
        UINT mask = ~(-1 << msb);
        return (*m_packed & mask) >> --lsb;
    }
}

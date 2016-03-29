#include "a429bnr.hpp"

namespace a429
{
    UINT a429bnr::operator= (UINT word)
    {
        *m_packed = word;
        return *m_packed;
    }

    void a429bnr::SetBit(int value, int pos)
    {
        if (value)
        {
            *m_packed |= 0x1 << (pos - 1);
            return *m_packed;
        }

        *m_packed &= ~(0x1 << (pos - 1));
    }

    UINT a429bnr::GetBit(int pos) const
    {
        return (*m_packed >> (pos - 1)) & 0x1;
    }

    a429bnr& a429bnr::SetBNR(double data)
    {
        unsigned int iData = (((unsigned int)(data / m_res)) & m_mask) << (m_endbit - m_sigbits);

        *m_packed &= ~(m_mask << (m_endbit - m_sigbits));
        *m_packed |= iData;

        if (m_signbit)
            SetBit((data <= -1 * m_res) || (data == (m_mask + 1) * m_res), m_signbit);

        return *this;
    }

    a429bnr& a429bnr::SetBNR(double data, double resolution, int sigbits, int endbit /*= 28 */, int signbit /*= 29 */)
    {
        SetBNRPropertiesA(resolution, sigbits, endbit, signbit);

        return SetBNR(data);
    }

    double a429bnr::GetBNR() const
    {
        short startbit = m_endbit - m_sigbits;
        unsigned int iData = (*m_packed & (m_mask << (startbit))) >> (startbit);
        double data = GetBit(m_signbit) ? (int)(iData | ~m_mask) * m_res : iData * m_res;

        return data;
    }

    double a429bnr::GetBNR(double resolution, int sigbits, int endbit /*= 28 */, int signbit /*= 29 */)
    {
        SetBNRPropertiesA(resolution, sigbits, endbit, signbit);

        return GetBNR();
    }

    a429bnr& a429bnr::SetBNRPropertiesA(double resolution, int sigbits, int endbit, int signbit)
    {
        m_res = resolution;
        m_sigbits = sigbits;
        m_endbit = endbit;
        m_signbit = signbit;

        m_mask = 1;
        for (int i = 0; i < m_sigbits; ++i) m_mask *= 2;
        m_mask -= 1;

        return *this;
    }

    a429bnr& a429bnr::SetBNRPropertiesB(double range, int sigbits, int endbit /*= 28 */, int signbit /*= 29 */)
    {
        double pow = 1.;
        for (int i = 0; i < sigbits; ++i) pow *= 2.;

        return SetBNRPropertiesA( (range) / pow , sigbits, endbit, signbit);
    }

    a429bnr& a429bnr::SetBNRPropertiesC(double resolution, int startbit, int endbit /*= 28 */, int signbit /*= 29 */)
    {
        return SetBNRPropertiesA(resolution, endbit-startbit+1, endbit, signbit);
    }

    a429bnr& a429bnr::SetBNRPropertiesD(double range, int startbit, int endbit /*= 28 */, int signbit /*= 29 */)
    {
        return SetBNRPropertiesB(range, endbit - startbit + 1, endbit, signbit);
    }
}

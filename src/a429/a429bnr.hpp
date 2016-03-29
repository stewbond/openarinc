#ifndef OPENARINC_A429BNR_HPP
#define OPENARINC_A429BNR_HPP

#include "a429base.hpp"

namespace a429
{
    enum SSM_BNR
    {
        BNR_FW    = 0,
        BNR_NCD   = 1,
        BNR_FT    = 2,
        BNR_NO    = 3,
    };

    class a429bnr : public virtual a429base
    {
    private:
        void SetBit(bool value, unsigned int pos);
        UINT GetBit(unsigned int pos) const;

    protected:
        double       m_res;
        short        m_sigbits;
        short        m_endbit;
        short        m_signbit;
        unsigned int m_mask;

    public:
        a429bnr() : a429base() {}
        a429bnr(UINT input) : a429base(input) {}
        a429bnr(UINT* reference) : a429base(reference) {}

        operator UINT() const { return *m_packed; }
        UINT operator= (UINT word);

        a429bnr& SetBNR(double data);
        a429bnr& SetBNR(double data, double resolution, int sigbits, int endbit = 28, int signbit = 29);

        double GetBNR() const;
        double GetBNR             (double resolution, int sigbits,  int endbit = 28, int signbit = 29);
        a429bnr& SetBNRPropertiesA(double resolution, int sigbits,  int endbit = 28, int signbit = 29);
        a429bnr& SetBNRPropertiesB(double range,      int sigbits,  int endbit = 28, int signbit = 29);
        a429bnr& SetBNRPropertiesC(double resolution, int startbit, int endbit = 28, int signbit = 29);
        a429bnr& SetBNRPropertiesD(double range,      int startbit, int endbit = 28, int signbit = 29);
    };
}

#endif // OPENARINC_A429BNR_HPP

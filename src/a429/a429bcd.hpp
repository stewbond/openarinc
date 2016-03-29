#ifndef OPENARINC_A429BCD_HPP
#define OPENARINC_A429BCD_HPP

#include "a429base.hpp"

namespace a429
{
    enum SSM_BCD
    {
        BCD_POS = 0,
        BCD_NCD = 1,
        BCD_FT  = 2,
        BCD_NEG = 3,
    };

    class a429bcd : public virtual a429base
    {
    protected:
        int       m_numdigits;
        double    m_res;

    public:
        // Constructors
        a429bcd() : a429base(), m_numdigits(5), m_res(1.0) {}
        a429bcd(UINT input) : a429base(input), m_numdigits(5), m_res(1.0) {}
        a429bcd(UINT* reference) : a429base(reference) {}

        // Operators
        operator UINT() const { return *m_packed; }
        UINT operator= (UINT word);

        a429bcd& SetBCD(double data);   // Easily sets BCD data into a word where the packing information is previously defined

        // Unpacking BCD data where packing information was previously defined.
        double GetBCD() const;

        // Sets properties of BCD words given resolution and # of DIGITs
        a429bcd& SetBCDProperties(double resolution, unsigned int numdigits );

        // Sets a single digit between 0 and 9
        a429bcd& SetDigit(unsigned int data, unsigned int startbit, unsigned int endbit);

        // Returns a single digit between 0 and 9
        UINT GetDigit(unsigned int startbit, unsigned int endbit) const;
    };
}

#endif // OPENARINC_A429BCD_HPP

#include "a429bcd.hpp"

namespace a429
{
    double fabs(double input)
    {
        return (input < 0)? -1*input : input;
    }

    UINT a429bcd::operator= (UINT word)
    {
        *m_packed = word;
        return *m_packed;
    }

    a429bcd& a429bcd::SetBCD(double data)
    {
        int tens[6] = { 1, 10, 100, 1000, 10000, 100000 };
        int i_data = 0;
        short EndBit = 0, StartBit = 0;
        double Epsilon = 0.00000001;

        // Zero the data to avoid residual leading non-zeros
        if      ( m_numdigits >  5 ) *m_packed &= 0xe00000ff;
        else if ( m_numdigits == 5 ) *m_packed &= 0xe00003ff;
        else if ( m_numdigits == 4 ) *m_packed &= 0xe0003fff;
        else if ( m_numdigits == 3 ) *m_packed &= 0xe003ffff;
        else if ( m_numdigits == 2 ) *m_packed &= 0xe03fffff;

        for(int k = 0; k < m_numdigits; k++)
        {
            if (m_res != 0.0)
            {
                i_data = (int)( (fabs(data) + Epsilon)/(m_res* tens[m_numdigits - k]) );
            }
            else
            {
                i_data = (int) (fabs(data) + Epsilon);
            }

            if ( m_numdigits > 5)
            {
                // | 29 | 28-27-26-25 | 24-23-22-21 | 20-19-18-17 | 16-15-14-13 | 12-11-10-09 |
                // | 1st|     2nd     |     3rd     |     4th     |     5th     |     6th     |

                if ( k == 0 )
                {
                    EndBit   = 29;
                    StartBit = 29;
                }
                else
                {
                    EndBit   = short (32 - 4*k);
                    StartBit = short (29 - 4*k);
                }
            }
            else
            {
                //  |  29-28-27   | 26-25-24-23 | 22-21-20-19 | 18-17-16-15 | 14-13-12-11 |
                //  |     1st     |     2rd     |     3th     |     4th     |     5th     |
                if ( k == 0)
                {
                    EndBit   = 29;
                    StartBit = 27;
                }
                else
                {
                    EndBit   = short (30 - 4*k);
                    StartBit = short (27 - 4*k);
                }
            }

            int digitData = i_data % 10;
            SetDigit(digitData, StartBit, EndBit);
        }

        return *this;
    }

    double a429bcd::GetBCD() const
    {
        int tens[6] = { 1, 10, 100, 1000, 10000, 100000 };
        int k = m_numdigits;
        double output = 0.0;

        if (k == 6)  // 6 digit config
        {
            output += tens[--k] * GetDigit(29, 29);
            output += tens[--k] * GetDigit(25, 28);
            output += tens[--k] * GetDigit(21, 24);
            output += tens[--k] * GetDigit(17, 20);
            output += tens[--k] * GetDigit(13, 16);
            output += tens[--k] * GetDigit( 9, 12);
        }
        else // 5 digit config
        {
            if (--k >= 0) output += tens[k] * GetDigit(27, 29);
            if (--k >= 0) output += tens[k] * GetDigit(23, 26);
            if (--k >= 0) output += tens[k] * GetDigit(19, 22);
            if (--k >= 0) output += tens[k] * GetDigit(15, 18);
            if (--k >= 0) output += tens[k] * GetDigit(11, 14);
        }

        output *= m_res;

        if (GetSSM() == BCD_NEG)
            output *= -1;

        return output;
    }

    a429bcd& a429bcd::SetBCDProperties(double resolution, unsigned int numdigits)
    {
        m_res = resolution;
        m_numdigits = numdigits; // warning, number of digits must not be more than 6
        return *this;
    }

    a429bcd& a429bcd::SetDigit(unsigned int data, unsigned int startbit, unsigned int endbit)
    {
        UINT mask = ~(-1 << endbit) & (-1 << (startbit-1));

        *m_packed &= ~mask; // Set these digits to 0
        *m_packed |= (data << (startbit-1)) & mask;

        return *this;
    }

    UINT a429bcd::GetDigit(unsigned int startbit, unsigned int endbit) const
    {
        UINT mask = ~(-1 << endbit) & (-1 << (startbit-1));

        return (*m_packed & mask) >> (startbit-1);
    }
}

#include "a429base.hpp"

namespace a429
{
    enum SSM_DIS
    {
        DIS_NO    = 0,
        DIS_NCD   = 1,
        DIS_FT    = 2,
        DIS_FW    = 3,
    };

    // Represents an A429 discrete label by providing discrete-specific methods
    class a429dis : public virtual a429base
    {
    public:

        a429dis() : a429base() {}
        a429dis(UINT input) : a429base(input) {}
        a429dis(UINT* reference) : a429base(reference) {}

        operator UINT() const { return *m_packed; }
        UINT operator= (UINT word);

        a429dis& SetBit (bool value, int pos);
        a429dis& SetBits(UINT value, int msb, int lsb);

        bool     GetBit (int pos) const;
        UINT     GetBits(int msb, int lsb) const;
    };
}


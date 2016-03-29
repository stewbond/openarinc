#include "a429base.hpp"
#include "a429bcd.hpp"
#include "a429bnr.hpp"
#include "a429dis.hpp"

namespace a429
{

    // Represents an A429 hybrid label by providing methods from all other types
    class a429hyb : public virtual a429base, public virtual a429bnr, public virtual a429dis, public virtual a429bcd
    {
    public:
        using a429dis::SetBit;
        using a429dis::GetBit;

        a429hyb()                : a429base() {}
        a429hyb(UINT input)      : a429base(input) {}
        a429hyb(UINT* reference) : a429base(reference) {}

        operator UINT() const { return *m_packed; }
        UINT operator= (UINT word); // Casting from a UINT is automatically handled
        
    };

    // The type A429 is a hybrid type which contains all methods from all types of A429 labels
    typedef a429hyb a429;
}


#include "a429hyb.hpp"

namespace a429
{
    UINT a429hyb::operator= (UINT word)
    {
        *m_packed = word;
        return *m_packed;
    }
}

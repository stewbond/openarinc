#include "a429base.hpp"

namespace a429
{
    // Utility table to reverse bits in a byte
    static const unsigned char rev_byte[256] =
    {// 0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09  0x0a  0x0b  0x0c  0x0d  0x0e  0x0f
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0, // 0x00
        0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, // 0x10
        0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4, // 0x20
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc, // 0x30
        0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2, // 0x40
        0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa, // 0x50
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6, // 0x60
        0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, // 0x70
        0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1, // 0x80
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9, // 0x90
        0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, // 0xa0
        0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd, // 0xb0
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3, // 0xc0
        0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb, // 0xd0
        0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7, // 0xe0
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff  // 0xf0
    };

    a429base::a429base()
        : m_myword(0), m_packed(&m_myword) {}

    a429base::a429base(const A429Base& copy)
        : m_myword(*copy.m_packed), m_packed(&m_myword) {}

    a429base::a429base(UINT in)
        : m_myword(in), m_packed(&m_myword) {}

    a429base::a429base(UINT* ref)
    {
        if (ref)
        {
            m_packed = ref;
        }
        else
        {
            m_myword = 0;
            m_packed = &m_myword;
        }
    }

    a429base::~a429base() {}

    UINT a429base::operator= (UINT word)
    {
        *m_packed = word;
        return *m_packed;
    }

    a429base& a429base::Link(UINT* pword)
    {
        m_packed = pword;
        return *this;
    }

    a429base& a429base::UnLink()
    {
        m_packed = &m_myword;
        return *this;
    }

    a429base& a429base::SetSDI(UCHAR value)
    {
        value &= 0x3;
        *m_packed &= 0xfffffcff;
        *m_packed |= value << 8;
        return *this;
    }

    a429base& a429base::SetSSM(UCHAR value)
    {
        value &= 0x3;
        *m_packed &= 0x9fffffff;
        *m_packed |= value << 29;
        return *this;
    }

    a429base& a429base::SetLbl(UCHAR value)
    {
        UINT label = rev_byte[value];
        *m_packed &= 0xffffff00;
        *m_packed |= label;
        return *this;
    }

    a429base& a429base::SetRevLbl(UCHAR value)
    {
        *m_packed &= 0xffffff00;
        *m_packed |= value;
        return *this;
    }

    a429base& a429base::SetPar()
    {
        *m_packed &= 0x7fffffff;
        *m_packed |= CalcPar() << 31;
        return *this;
    }

    a429base& a429base::SetPar(bool p)
    {
        if (p)
            *m_packed |= 80000000;
        else
            *m_packed &= 0x7fffffff;

        return *this;
    }

    UCHAR a429base::GetSDI() const
    {
        return (*m_packed >> 8) & 0x3;
    }

    UCHAR a429base::GetSSM() const
    {
        return (*m_packed >> 29) & 0x3;
    }

    UCHAR a429base::GetLbl() const
    {
        return  rev_byte[*m_packed & 0xff];
    }

    UCHAR a429base::GetRevLbl() const
    {
        return (*m_packed & 0xff);
    }

    UCHAR a429base::GetPar() const
    {
        return ( *m_packed & 0x80000000 ) ? 1 : 0;
    }

    UINT a429base::GetWord() const
    {
        return *m_packed;
    }

    UCHAR a429base::CalcPar() const
    {
        unsigned int x = *m_packed & 0x7fffffff;
        x ^= x >> 16;
        x ^= x >>  8;
        x ^= x >>  4;
        x &= 0x0F;
        return ((0x6996 >> x) & 1);
    }
}
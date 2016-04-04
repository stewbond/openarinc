#ifndef OPENARINC_CIRCBUF_HPP
#define OPENARINC_CIRCBUF_HPP

#include "bufbase.hpp"

namespace buf
{

class circbuf_rx : public bufbase_rx
{
public:

    circbuf_rx(unsigned int* buf, unsigned int size)
        : m_buf(buf), m_size(size), m_lastindex(0) {}

    void recieve()
    {
        unsigned int newindex = m_buf[0];
        if (newindex == 0 || newindex == m_lastindex)
            return;

        if (newindex < m_lastindex)
        {
            while (++m_lastindex < m_size)
                process(m_buf[m_lastindex]);

            m_lastindex = 0;
        }

        while (newindex > m_lastindex++)
            process( m_buf[m_lastindex] );
    }

private:
    unsigned int* m_buf;
    unsigned int m_size;
    unsigned int m_lastindex;
};


class circbuf_tx
{
public:

    circbuf_tx(unsigned int* buf, unsigned int size)
        : m_buf(buf), m_size(size) {}

    send(unsigned int word)
    {
        unsigned int nextindex = m_buf[0] + 1;

        if (nextindex >= m_size) nextindex = 1;

        m_buf[nextindex] = word;
        m_buf[0] = nextindex; // It's critical that the last thing we do is increment this index (thread safety).
    }

private:
    unsigned int* m_buf ;
    unsigned int  m_size;
};

} // namespace buf

#endif // OPENARINC_CIRCBUF_HPP
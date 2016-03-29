#include <functional>
#include <vector>

class circbuf_rx
{
public:
    typedef std::function<void(unsigned int)> callback_type;

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


    void registr(callback_type func)
    {
        m_listeners.push_back(func);
    }

protected:
    void process(unsigned int word)
    {
        for (std::vector<callback_type>::iterator it = m_listeners.begin;
                                                  it != m_listeners.end;
                                                  ++it)
            (*it)(word);
    }

private:
    unsigned int* m_buf;
    unsigned int m_size;
    unsigned int m_lastindex;

    std::vector<callback_type> m_listeners;
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

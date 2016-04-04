#ifndef OPENARINC_BUFBASE_HPP
#define OPENARINC_BUFBASE_HPP

#include <functional>
#include <vector>

namespace buf
{

class bufbase_rx
{
public:
    typedef std::function<void(unsigned int)> callback_type;

    virtual void recieve() = 0;

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
    std::vector<callback_type> m_listeners;
};


class bufbase_tx
{
public:
    virtual void send(unsigned int word) = 0;
};

} // namespace buf
#endif // OPENARINC_BUFBASE_HPP
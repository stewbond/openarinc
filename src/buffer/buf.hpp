#ifndef OPENARINC_BUF_HPP
#define OPENARINC_BUF_HPP

#iniclude "circbuf.hpp"

namespace buf {

template <class T> class buf_rx {};

template <> class buf_rx<circbuf_rx> : public circbuf_rx
{
public:
	buf_rx(unsigned int* buf, unsigned int size) : circbuf_rx(buf, size) {}
};

template <class T> class buf_tx {};

template <> class buf_tx<circbuf_tx> : public circbuf_tx
{
public:
	buf_tx(unsigned int* buf, unsigned int size) : circbuf_tx(buf, size) {}
};

/*
template <> class buf_tx<sockbuf_tx> : public sockbuf_tx
{
public: 
	buf_tx() : sockbuf_tx(IP, Port) {}
}
*/

} // namespace buf

#endif
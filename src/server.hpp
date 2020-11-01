#pragma once

#include <netinet/in.h>

#include "types.hpp"

#include "client.hpp"

namespace sar {

/**
 * @brief basic abstract server class
 */
class server {
public:
	server();
	virtual ~server();

	virtual Protocol protocol() const;
	virtual Version version() const;

	void open();
	void close();

	void bind(unsigned short port);
	void listen(unsigned int backlog = 5);

	void accept(client& c);

private:
	// socket id
	int m_sid;

	// port
	unsigned short m_port;
	sockaddr_in sockaddr() const;
};

}

#pragma once

#include <netinet/in.h>

#include "types.hpp"

#include "client.hpp"

namespace sar {

/**
 * @brief Server class for listening on the server side.
 */
class server {
public:
	server();
	virtual ~server();

	/**
	 * @brief The server's protocol
	 *
	 * @return TCP or UDP
	 */
	virtual Protocol protocol() const;
	/**
	 * @brief The server's version
	 *
	 * @return IPV4 or IPV6
	 */
	virtual Version version() const;

	/**
	 * @brief Open the socket
	 *
	 * @remarks Called on construction.
	 */
	void open();
	/**
	 * @brief Close the socket
	 *
	 * @remarks Call open() to restart it for usage again.
	 */
	void close();

	/**
	 * @brief Bind the socket to a port.
	 *
	 * @param port The port to bind to
	 */
	void bind(unsigned short port);
	/**
	 * @brief Listen on the port specified in bind().
	 *
	 * @param backlog The amount of incoming connections to be able to be queued. Default of 5.
	 */
	void listen(unsigned int backlog = 5);

	/**
	 * @brief Accept a new client
	 *
	 * @param c The uninitialized client socket to fill.
	 */
	void accept(client& c);

private:
	// socket id
	int m_sid;

	// port
	unsigned short m_port;
	// the computed sockaddr_in struct
	sockaddr_in sockaddr() const;
};

}

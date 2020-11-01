#pragma once

#include "types.hpp"

#include <string>

namespace sar {

/**
 * @brief Used to connect to a server on the client side.
 */
class socket {
public:
	socket();
	virtual ~socket();

	/**
	 * @brief The protocol this socket uses.
	 *
	 * @return TCP or UDP
	 */
	virtual Protocol protocol() const;
	/**
	 * @brief The internet protocol version used
	 *
	 * @return IPV4 / IPV6
	 */
	virtual Version version() const;

	/**
	 * @brief Opens the socket
	 *
	 * @remarks Called on the socket's constructor.
	 */
	void open();
	/**
	 * @brief Closes the socket
	 *
	 * @remarks Call open() to use the socket again.
	 */
	void close();

	/**
	 * @brief Connect to a server
	 *
	 * @param ip The ip address of the server
	 * @param port The port to connect to
	 */
	void connect(const std::string& ip, unsigned short port);

	/**
	 * @brief Send data to the server
	 *
	 * @param buf The buffer to send
	 * @param len The amount of bytes to send
	 */
	void send(const char* buf, size_t len);
	/**
	 * @brief Receives data up until a null terminator.
	 *
	 * @remarks Be sure to delete[] the returned buffer.
	 * @remarks TODO: Use Modern STL for this.
	 *
	 */
	char* recv();

private:
	// internal socket id
	int m_sid;
};

}

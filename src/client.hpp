#pragma once

#include <cstddef>

namespace sar {

class server;

/**
 * @brief A client accepted by the server
 */
class client {
public:
	client();
	~client();

	/**
	 * @brief Send data to the client
	 *
	 * @param bytes The bytes to send
	 * @param len How many bytes to send
	 */
	void send(const char* bytes, size_t len);

	/**
	 * @brief Receive bytes until a NULL byte is reached.
	 *
	 */
	char* recv();

private:
	friend class server;

	/// internal socket id
	int m_sid;
};

}

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

	virtual Protocol protocol() const;
	virtual Version version() const;

	void open();
	void close();

	void connect(const std::string& ip, unsigned short port);

	void send(const char* buf, size_t len);
	char* recv();

private:
	// internal socket id
	int m_sid;
};

}

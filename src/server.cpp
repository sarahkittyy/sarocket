#include "server.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>

namespace sar {

server::server()
	: m_sid(0),
	  m_port(0) {
	open();
}

server::~server() {
	close();
}

Protocol server::protocol() const {
	return Protocol::TCP;
}

Version server::version() const {
	return Version::IPV4;
}

void server::open() {
	m_sid = ::socket(version(), protocol(), 0);
	if (m_sid == 0) {
		throw std::runtime_error("Could not create socket.");
	}
}

void server::close() {
	::close(m_sid);
}

void server::bind(unsigned short port) {
	if (m_sid == 0) {
		throw std::runtime_error("Invalid socket id in bind()");
	}

	m_port = port;

	sockaddr_in addr = sockaddr();
	int err			 = ::bind(m_sid, (struct sockaddr*)&addr, sizeof(addr));
	if (err < 0) {
		throw std::runtime_error("Could not bind socket on port " +
								 std::to_string(ntohs(addr.sin_port)) + ": " +
								 std::string(std::strerror(errno)));
	}
}

void server::listen(unsigned int backlog) {
	int err = ::listen(m_sid, backlog);
	if (err < 0) {
		throw std::runtime_error("Could not listen on socket: " +
								 std::string(std::strerror(errno)));
	}
}

void server::accept(client& c) {
	sockaddr_in addr  = sockaddr();
	socklen_t addrlen = sizeof(struct sockaddr_in);
	c.m_sid			  = ::accept(m_sid, (struct sockaddr*)&addr, &addrlen);
	if (c.m_sid < 0) {
		throw std::runtime_error("Could not accept client.");
	}
}

sockaddr_in server::sockaddr() const {
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family		 = version();
	addr.sin_port		 = htons(m_port);
	return addr;
}

}

#include "socket.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>
#include <vector>

namespace sar {

socket::socket()
	: m_sid(0) {
	open();
}

socket::~socket() {
	close();
}

Protocol socket::protocol() const {
	return Protocol::TCP;
}

Version socket::version() const {
	return Version::IPV4;
}

void socket::open() {
	m_sid = ::socket(version(), protocol(), 0);
	if (m_sid == 0) {
		throw std::runtime_error("Could not open socket.");
	}
}

void socket::close() {
	::close(m_sid);
}

void socket::connect(const std::string& ip, unsigned short port) {
	int err;
	sockaddr_in addr;

	addr.sin_family = version();
	addr.sin_port	= htons(port);
	err				= inet_pton(version(), ip.c_str(), &addr.sin_addr);

	if (err <= 0) {
		throw std::runtime_error("Invalid ip address specified.");
	}

	err = ::connect(m_sid, (struct sockaddr*)&addr, sizeof(addr));
	if (err < 0) {
		throw std::runtime_error("Could not connect to server.");
	}
}

void socket::send(const char* buf, size_t len) {
	if (m_sid == 0) {
		throw std::runtime_error("Socket id not valid!");
	}

	int total = 0;
	do {
		int sent = ::send(m_sid, buf + total, len - total, 0);
		if (sent < 0) {
			throw std::runtime_error("Error sending data.");
		}
		total += sent;
	} while (total < len);
}

char* socket::recv() {
	if (m_sid == 0) {
		throw std::runtime_error("Socket id not valid!");
	}

	std::vector<char> buf;

	int total = 0;
	for (;;) {
		char c;
		int read = ::recv(m_sid, &c, 1, 0);
		total += read;
		if (read < 0) {
			throw std::runtime_error("Could not read data.");
		} else if (read == 0 && total != 0) {
			break;
		} else {
			buf.push_back(c);
			if (c == '\0') {
				break;
			}
		}
	}

	char* res = new char[total]{ 0 };
	std::memcpy(res, &buf[0], total);

	return res;
}

}

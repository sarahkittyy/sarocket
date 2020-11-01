#include "client.hpp"

#include <sys/socket.h>

#include <cstring>
#include <stdexcept>
#include <vector>

namespace sar {

client::client()
	: m_sid(0) {
}

client::~client() {
}

void client::send(const char* bytes, size_t len) {
	if (m_sid == 0) {
		throw std::runtime_error("Client has no valid socket id.");
	}

	int total = 0;
	do {
		int sent = ::send(m_sid, bytes + total, len - total, 0);
		if (sent < 0) {
			throw std::runtime_error("Error sending to client.");
		}
		total += sent;
	} while (total < len);
}

char* client::recv() {
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

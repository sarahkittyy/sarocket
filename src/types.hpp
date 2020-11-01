#pragma once

#include <sys/socket.h>

/// Simple type abstractions over common constants
namespace sar {

enum Protocol {
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM,
};

enum Version {
	IPV4 = AF_INET,
	IPV6 = AF_INET6
};

}

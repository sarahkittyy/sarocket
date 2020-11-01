#include <catch2/catch.hpp>
#include <cstring>
#include <thread>

#include "sarocket.hpp"

TEST_CASE("Sockets can be created and bound.", "[socket]") {
	sar::server s;
	SECTION("the socket can be setup and bound to a port") {
		s.bind(8080);
		s.listen();
		SUCCEED("socket did not throw");
	}
}

TEST_CASE("Sockets can be bound and accept clients.", "[socket]") {
	const unsigned short PORT = 9000;
	sar::server s;
	s.bind(PORT);
	s.listen();
	INFO("server bound and listening");

	std::thread cli([]() {
		sar::socket s;
		s.connect("127.0.0.1", PORT);
		char* buf		= s.recv();
		std::string ret = "got string " + std::string(buf);
		s.send(ret.c_str(), ret.size());
		delete[] buf;
	});
	INFO("client thread launched");

	sar::client c;
	s.accept(c);
	INFO("client accepted");

	const char* str = "my-data lmao";
	c.send(str, strlen(str) + 1);
	char* buf = c.recv();
	REQUIRE(std::string(buf) == "got string " + std::string(str));
	delete[] buf;

	cli.join();

	SUCCEED("thread joined.");
}

TEST_CASE("Sockets can be closed and re-bound.", "[socket]") {
	const unsigned short PORT = 9000;
	sar::server s;
	s.bind(PORT);
	s.listen();

	s.close();

	s.open();
	s.bind(PORT);
	s.listen();

	SUCCEED("socket re-bound successfully.");
}

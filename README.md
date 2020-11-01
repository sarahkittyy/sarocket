# sarocket ![](https://img.shields.io/github/workflow/status/sarahkittyy/sarocket/CMake)

## Dependencies

- pthread

### Optional

- [Catch2 v2.x](https://github.com/catchorg/Catch2/tree/v2.x) (For unit testing)

## Building

```bash
git clone https://github.com/sarahkittyy/sarocket
cd sarocket/build
cmake \
	-DBUILD_TESTS=on \ # if you want tests enabled
	..
make
```

## Running the tests

```bash
make test
```

## Example

server.cpp
```cpp
#include <sarocket.hpp>
#include <cstdio>
#include <cstring>

int main() {
	sar::server serv;
	serv.bind(8080);
	serv.listen();

	sar::client c;
	serv.accept(c);

	const char* data = "hello from server!";
	c.send(data, strlen(data));

	return 0;
}

```

client.cpp
```cpp
#include <sarocket.hpp>
#include <cstdio>

int main() {
	sar::socket s;
	s.connect("localhost", 8080);

	char* buf = s.recv();

	std::printf("received string: %s\n", buf);

	delete[] buf;
	return 0;
}
```

client output: `received string: hello from server!`

## Docs

Docs located at https://sarahkittyy.github.io/sarocket

## TODO

- [ ] Universal packet type.
- [ ] Stream operations
- [ ] Support for STL container and types (`std::string`, `std::vector`)
- [ ] Natural support for UDP and IPV6
- [ ] More abstraction over send / recv

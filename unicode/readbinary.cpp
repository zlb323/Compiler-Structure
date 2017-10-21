#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>

int main(int argc, char *argv[]) {
  uint64_t offset = 0;
  for (int i=1; i<argc; ++i) {
    std::ifstream in(argv[i], std::ios::in | std::ios::binary);
    for (;;) {
      int value = in.get();
      if (value == -1) break;
      uint8_t byte = value;
      std::cout
	<< "offset " << std::dec << std::setw(4) << std::setfill(' ') << offset
	<< " is "
	<< std::hex << std::setw(2) << std::setfill('0') << ((int) byte)
	<< std::endl;
      ++offset;
    }
  }
  return 0;
}

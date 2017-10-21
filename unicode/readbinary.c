#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[]) {
  uint32_t offset = 0;
  int i;
  for (i=1; i<argc; ++i) {
    FILE *in = fopen(argv[i], "rb");
    for (;;) {
      int value = fgetc(in);
      if (value == -1) break;
      uint8_t byte = value;
      printf("offset %4d is 0x%02x\n",offset,(int) byte);
      ++offset;
    }
  }
  return 0;
}

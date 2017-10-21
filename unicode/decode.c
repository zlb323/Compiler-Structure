






















#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t decode1(uint8_t *utf8)
{
  uint32_t codepoint = ((((uint32_t) utf8[0]) & 0x7F) << 0);
  return codepoint;
}

uint32_t decode2(uint8_t *utf8)
{
  uint32_t codepoint = 
    ((((uint32_t) utf8[0]) & 0x1F) << 6)|
    ((((uint32_t) utf8[1]) & 0x3F) << 0);
  return codepoint;
}

uint32_t decode3(uint8_t *utf8)
{
  uint32_t codepoint =
    ((((uint32_t) utf8[0]) & 0x0F) << 12)|
    ((((uint32_t) utf8[1]) & 0x3F) << 6)|
    ((((uint32_t) utf8[2]) & 0x3F) << 0);

  return codepoint;
}

uint32_t decode4(uint8_t *utf8)
{
  uint32_t codepoint =
    ((((uint32_t) utf8[0]) & 0x03) << 18)|
    ((((uint32_t) utf8[1]) & 0x3F) <<12)|    
    ((((uint32_t) utf8[1]) & 0x3F) << 6)|
    ((((uint32_t) utf8[2]) & 0x3F) << 0);

  return codepoint;
}

void process(FILE *in) {
  uint8_t utf8[5];
  int bytes;
  for (;;) {
    int c = fgetc(in);
    if (c == -1) break;
    utf8[0]=c;
    if ((c & 0x80) == 0) {
      bytes = 1;
    } else if ((c & 0xE0) == 0xC0) {
      bytes = 2;
    } else if ((c & 0xF0) == 0xE0) {
      bytes = 3;
    } else if ((c & 0xF8) == 0xF0) {
      bytes = 4;
    } else {
      printf("invalid utf8 encoding 1\n");
      continue;
    }
    int byte=1;
    while (byte < bytes) {
      c = fgetc(in);
      if ((c == -1) || (c & 0xC0) != 0x80) {
	printf("invalid utf8 encoding 2\n");
	continue;
      }
      utf8[byte]=c;
      ++byte;
    }

    utf8[bytes]=0;

    int codepoint;
    switch(bytes) {
    case 1: codepoint=decode1(utf8); break;
    case 2: codepoint=decode2(utf8); break;
    case 3: codepoint=decode3(utf8); break;
    case 4: codepoint=decode4(utf8); break;
    }

    printf("'%s'",utf8);
    printf(" = utf8(");
    for (byte = 0; byte<bytes; ++byte) {
      if (byte > 0) printf(",");
      printf("0x%02x=%d",utf8[byte],utf8[byte]);
    }
    printf(")");
    printf(" = codepoint(0x%04x=%d)\n",codepoint,codepoint);
  }
}

int main(int argc, char *argv[]) {
  int argi;
  for (argi = 1; argi<argc; ++argi) {
    FILE *in = fopen(argv[argi],"rb");
    if (in == 0) {
      printf("Could not open file %s.\n",argv[argi]);
      exit(1);
    }
    process(in);
    fclose(in);
  }
}

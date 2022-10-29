#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u8 gsmg_code[17] = {0x5b, 0x66, 0x7d, 0x7f};

void delay(u16 us) {
  while (us--) {
  }
}

int main() {
  int i;
  LSC = 1;
  LSB = 1;
  LSA = 1;
  while (1) {
    for (i = 0; i < 4; i++) {
      P0 = gsmg_code[i];
      delay(10000);
    }
  }
  return 0;
}
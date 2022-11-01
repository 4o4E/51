#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;
sbit KEY0 = P3 ^ 1;

u8 gsmg_code[17] = {0x7d, 0x7f};

void delay(u16 us) {
  while (us--) {
  }
}

int main() {
  int i, t, l0 = 0;
  LSC = 1;
  LSB = 1;
  LSA = 1;
  while (1) {
    if (KEY0 == 0) {
      if (l0 == 0)
        t = 0;
      else
        l0 = 0;
    } else {
      if (l0 == 1)
        t = 1;
      else
        l0 = 1;
    }
    for (i = 0; i < 8; i++) {
      // 设置数码管位数
      switch (i) {
        case 0:
          LSC = 1, LSB = 1, LSA = 1;
          break;
        case 1:
          LSC = 1, LSB = 1, LSA = 0;
          break;
        case 2:
          LSC = 1, LSB = 0, LSA = 1;
          break;
        case 3:
          LSC = 1, LSB = 0, LSA = 0;
          break;
        case 4:
          LSC = 0, LSB = 1, LSA = 1;
          break;
        case 5:
          LSC = 0, LSB = 1, LSA = 0;
          break;
        case 6:
          LSC = 0, LSB = 0, LSA = 1;
          break;
        case 7:
          LSC = 0, LSB = 0, LSA = 0;
          break;
      }
      // 设置显示
      P0 = gsmg_code[t];
      delay(100);
    }
  }
  return 0;
}
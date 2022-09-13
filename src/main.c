#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;

u8 gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

void delay(u16 us) {
  while (us--) {
  }
}

static u16 press[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 扫描按下的按键并存到数组press中
void scan() {
  // 初始化数组press
  int i = 0;
  for (i = 0; i < 16; i++) {
    press[i] = 0;
  }

  P1 = 0xf7;          // 1111 0111 给第一列赋值0，其余全为1
  delay(1000);        // 消抖
  if (P1 >> 7 & 0x1)  // 0111 0111 0X77
    press[0] = 1;
  if (P1 >> 6 & 0x1)  // 1011 0111 0Xb7
    press[4] = 1;
  if (P1 >> 5 & 0x1)  // 1101 0111
    press[8] = 1;
  if (P1 >> 4 & 0x1)  // 1110 0111
    press[12] = 1;

  P1 = 0xfb;          // 1111 1011 给第二列赋值0，其余全为1
  delay(1000);        // 消抖
  if (P1 >> 7 & 0x1)  // 0111 1011
    press[1] = 1;
  if (P1 >> 6 & 0x1)  // 1011 1011
    press[5] = 1;
  if (P1 >> 5 & 0x1)  // 1101 1011
    press[9] = 1;
  if (P1 >> 4 & 0x1)  // 1110 1011
    press[13] = 1;

  P1 = 0xfd;          // 1111 1101 给第三列赋值0，其余全为1
  delay(1000);        // 消抖
  if (P1 >> 7 & 0x1)  // 0111 1101
    press[2] = 1;
  if (P1 >> 6 & 0x1)  // 1011 1101
    press[6] = 1;
  if (P1 >> 5 & 0x1)  // 1101 1101
    press[10] = 1;
  if (P1 >> 4 & 0x1)  // 1110 1101
    press[14] = 1;

  P1 = 0xfe;          // 1111 1110 给第四列赋值0，其余全为1
  delay(1000);        // 消抖
  if (P1 >> 7 & 0x1)  // 0111 1110
    press[3] = 1;
  if (P1 >> 6 & 0x1)  // 1011 1110
    press[7] = 1;
  if (P1 >> 5 & 0x1)  // 1101 1110
    press[11] = 1;
  if (P1 >> 4 & 0x1)  // 1110 1110
    press[15] = 1;
}

int main() {
  int i = 0;
  int count = 0;
  while (1) {
    scan();
    count = 0;
    for (i = 0; i < 16; i++) {
      if (press[i] == 1) {
        count++;
      }
    }

    P0 = gsmg_code[16 - count];
    delay(1000);
  }
  return 0;
}
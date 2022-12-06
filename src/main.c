#include "reg51.h"
#include "intrins.h"

#define L1 0
#define L2 1
#define L3 2
#define L4 3
#define L5 4
#define L6 5
#define L7 6
#define M1 7
#define M2 8
#define M3 9
#define M4 10
#define M5 11
#define M6 12
#define M7 13
#define H1 14
#define H2 15
#define H3 16
#define H4 17
#define H5 18
#define H6 19
#define H7 20

typedef unsigned int u16;
typedef unsigned char u8;

sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;

sbit BEEP = P2 ^ 5;

// 频率(循环间隔)
unsigned char arr[21] = {
  1908, 1700, 1516, 1433, 1276, 1136, 1012,
  956, 842, 759, 716, 638, 568, 506,
  478, 426, 372, 358, 319, 284, 253
};

// [音符, 节拍长]
unsigned char music[33][2] = {
  {L6, 4}, {L6, 1}, {L6, 2}, {L6, 2}, {M3, 4}, {M3, 2}, {M3, 2}, {M2, 4}, {M3, 4}, {M1, 8},
  {M2, 2}, {M2, 2}, {M2, 2}, {L6, 2}, {M2, 4}, {M2, 4}, {M5, 2}, {M5, 2}, {M5, 2}, {M6, 2}, {M3, 8},
  {L6, 4}, {L6, 3}, {L6, 1}, {M3, 4}, {M3, 2}, {M3, 2}, {M2, 2}, {M2, 1}, {M2, 1}, {M3, 2}, {M2, 2}, {M1, 8},
  // {L7, 3}, {L7, 1}, {L7, 2}, {L6, 2}, {L5, 4}, {L3, 4}, {L7, 2}, {L7, 4}, {L7, 2}, {M1, 4}, {L7, 4}, {L6, 16}, 
};

void delay(u16 us) {
  while (us--);
}

int main() {
  unsigned long j, l;
  u8 i, k, a;
  for (i = 0; i < 33; i++) {
    a = music[i][0]; // 音符
    k = arr[a + 6] * 10 / 12; // 频率
    l = music[i][1] * 6000 / k; // 节拍长
    for (j = 0; j < l; j++) {
      BEEP = 0;
      delay(k);
      BEEP = 1;
      delay(k);
    }
    delay(2000); // 停顿
  }
  while (1) {}
  return 0;
}
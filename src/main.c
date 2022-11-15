#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit KEY3 = P3 ^ 2;
sbit KEY4 = P3 ^ 3;
sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

void delay(u16 us) {
  while (us--) {
  }
}

void init0() {
  IT0 = 1;
  EX0 = 1;
  EA = 1;
}

void init1() {
  IT1 = 1;
  EX1 = 1;
  EA = 1;
}

static int i, j, k;

int arr1492[] = {0x06, 0x66, 0x6f, 0x5b};

// 数码管动态扫描方法显示 1 4 9 2（循环5次）
void exti0() interrupt 0 {
  if (KEY3 != 0)
    return;
  for (j = 0; j < 5; j++) {
    for (k = 0; k < 500; k++) {
      for (i = 0; i < 4; i++) {
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
        }
        // 设置显示
        P0 = arr1492[i];
        delay(10);
      }
    }
    for (i = 0; i < 4; i++) {
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
      }
      // 设置显示
      P0 = 0;
      delay(10);
    }
    delay(500000);
  }
}

// 驱动8只LED灯奇数灯与偶数灯交叉闪烁（循环5次）
void exti1() interrupt 2 {
  delay(1000);
  if (KEY4 != 0)
    return;
  for (i = 0; i < 5; i++) {
    P2 = 85;
    delay(20000);
    P2 = ~P2;
    delay(20000);
  }
  P2 = 0xff;
}

int main() {
  init0();
  init1();
  while (1) {
  }
  return 0;
}
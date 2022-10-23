#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit KEY0 = P3 ^ 1;
sbit KEY1 = P3 ^ 0;
sbit KEY2 = P3 ^ 2;
sbit KEY3 = P3 ^ 3;

sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;
sbit LED2 = P2 ^ 2;
sbit LED3 = P2 ^ 3;

sbit LED7 = P2 ^ 7;

void delay(u16 us) {
  while (us--) {
  }
}

int main() {
  int l0 = 0,
      l1 = 0,
      l2 = 0,
      l3 = 0;

  while (1) {
    if (KEY0 == 0) {
      if (l0 == 0)
        LED0 = 0;
      else
        l0 = 0;
    }
    else {
      if (l0 == 1)
        LED0 = 1;
      else
        l0 = 1;
    }

    if (KEY1 == 0) {
      if (l1 == 0)
        LED1 = 0;
      else
        l1 = 0;
    }
    else {
      if (l1 == 1)
        LED1 = 1;
      else
        l1 = 1;
    }
    
    if (KEY2 == 0) {
      if (l2 == 0)
        LED2 = 0;
      else
        l2 = 0;
    }
    else {
      if (l2 == 1)
        LED2 = 1;
      else
        l2 = 1;
    }
    
    if (KEY3 == 0) {
      if (l3 == 0)
        LED3 = 0;
      else
        l3 = 0;
    }
    else {
      if (l3 == 1)
        LED3 = 1;
      else
        l3 = 1;
    }

    delay(500);  
  }

  return 0;
} 
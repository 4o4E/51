#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit LED0 = P2 ^ 0;

void init0() {
  TMOD |= 0X01;            //选择为定时器0模式 工作方式1
  TH0 = 0XFC, TL0 = 0X18;  //给定时器赋初值 定时1ms
  ET0 = 1;                 //打开定时器0中断允许
  EA = 1;                  //打开总中断
  TR0 = 1;                 //打开定时器
}

void exti0() interrupt 1 {
  static u16 i;            //定义静态变量i
  TH0 = 0XFC, TL0 = 0X18;  //给定时器赋初值，定时1ms
  i++;
  if (i == 65) {
    i = 0;
    LED0 = !LED0;
  }
}

int main() {
  init0();
  while (1) {
  }
  return 0;
}
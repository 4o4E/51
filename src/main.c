#include "reg51.h"

// 音符下标
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

#define END 21

typedef unsigned int uint;
typedef unsigned char uchar;

sbit sound = P2 ^ 5;

// 储存音符对应的频率
// 单独存放减少RAM和ROM的占用
// 播放时通过下标获取
uint code RATE[] = {
  262, 286, 311, 349, 392, 440, 494,
  523, 587, 659, 698, 784, 880, 987,
  1046, 1174, 1318, 1396, 1567, 1760, 1975,
  0xff // 代表乐曲结束
};

// 乐曲信息
// [音符, 节拍]
uchar code MUSIC[][2] = {
  {L6, 4}, {L6, 1}, {L6, 2}, {L6, 2}, {M3, 4}, {M3, 2}, {M3, 2}, {M2, 4}, {M3, 4}, {M1, 8},
  {M2, 2}, {M2, 2}, {M2, 2}, {L6, 2}, {M2, 4}, {M2, 4}, {M5, 2}, {M5, 2}, {M5, 2}, {M6, 2}, {M3, 8},
  {L6, 4}, {L6, 3}, {L6, 1}, {M3, 4}, {M3, 2}, {M3, 2}, {M2, 2}, {M2, 1}, {M2, 1}, {M3, 2}, {M2, 2}, {M1, 8},
  {L7, 3}, {L7, 1}, {L7, 2}, {L6, 2}, {L5, 4}, {L3, 4}, {L7, 2}, {L7, 4}, {L7, 2}, {M1, 4}, {L7, 4}, {L6, 16},
  {M6, 4}, {M6, 3}, {M5, 1}, {M6, 4}, {M3, 4}, 
  {M5, 4}, {M1, 3}, {M2, 1}, {M3, 4}, {M3, 4}, 
  {M2, 3}, {M2, 1}, {M2, 2}, {M2, 2}, {M2, 4}, {M2, 4}, {M5, 4}, {M6, 4}, {M3, 8},
  {M6, 4}, {M6, 3}, {M5, 1}, {M6, 4}, {M3, 4}, 
  {M7, 4}, {M7, 3}, {M7, 1}, {M6, 4}, {M3, 4}, 
  {M2, 3}, {M2, 1}, {M2, 2}, {M2, 2}, {M2, 2}, {M2, 2}, {M1, 3}, {M2, 1}, {M3, 4}, {M7, 4}, {M6, 8},
  {END, 0} 
};

// 延时
void delay(uchar count) {
  uchar i, j;
  for(i = 0; i < count; i++) for(j = 0; j < 250; j++);
}

uint C, // 定时常数
     n, // 当前频率
     l; // 当前节拍
uchar index = 0, // 节拍下标
      temp,      // 循环用的变量
      row,     // 当前扫描的行
      column,  // 当前扫描的列
      stat;    // 按键状态

int getPress() {
  // 等待用户按键
  do {
    P1 = 0xf0;
    stat = P1;
    stat = stat & 0xf0;
  } while(stat == 0xf0);
  P1 = 0xf0;
  stat = P1 & 0xf0;
  // 判断按键列
  switch(stat) {
    case 0xe0: column = 1; break;
    case 0xd0: column = 2; break;
    case 0xb0: column = 3; break;
    case 0x70: column = 4; break;
  }
  P1 = 0x0f;
  stat = P1;
  stat = stat & 0x0f;
  // 判断按键行
  switch(stat) {
    case 0x0e: row = 1; break;
    case 0x0d: row = 2; break;
    case 0x0b: row = 3; break;
    case 0x07: row = 4; break;
  }
  return (row - 1) * 4 + column - 1; // 按键值
}

void main(void) {
  // 定时器
  TMOD = 0x00, EA = 1, ET0 = 1;
  while(1) {
    if(getPress() != 15) continue; // 忽略其他按下的按键
    while(1) {
      n = RATE[MUSIC[index][0]]; // 从
      if (n == 0xff) break;  // 0xff -> 结束
      l = MUSIC[index][1];
      C = 500000 / n; 	// 1/2*10^6 μs 用取到的音符频率计算对应的半周期
      TH0 = (8192 - C) / 32;  // 13位计数器TH0高8位赋初值
      TL0 = (8192 - C) % 32;  // 13位计数器TL0低5位赋初值
      TR0 = 1;                // 启动定时器T0
      for(temp = 0; temp < l; temp++) delay(160); // 187
      TR0 = 0; // 关闭定时器T0
      delay(50);
      index++; // 播放下一个音符
    }
    index = 0;
  }
}

void time() interrupt 1 {
  sound = !sound;    // 使蜂鸣器震动
  TH0 = (8192 - C) / 32; // 13位计数器TH0高8位赋初值
  TL0 = (8192 - C) % 32; // 13位计数器TL0低5位赋初值
}
#include "reg52.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;
sbit LED2 = P2 ^ 2;
sbit LED3 = P2 ^ 3;
sbit LED4 = P2 ^ 4;
sbit LED5 = P2 ^ 5;
sbit LED6 = P2 ^ 6;
sbit LED7 = P2 ^ 7;

// 获取将x的第y位
u8 getBit(u8 x, u8 y) {
  return (u8)(x >> (7 - y) & 1);
}

// 将X的第Y位置1
u8 setBit(u8 x, u8 y) {
  return x | 1 << (7 - y);
}

// 将X的第Y位清0
u8 clrBit(u8 x, u8 y) {
  return x & ~(1 << (7 - y));
}

void delay(u16 us) {
  while (us--) {
  }
}

sbit SRCLK = P3 ^ 6;
sbit RCLK_ = P3 ^ 5;
sbit SER = P3 ^ 4;

// 每列对应的二进制
static u8 lineBuf[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
// 列数据
static u8 colBuf[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

void write(u8 d) {
  u8 i = 0;
  for (i = 0; i < 8; i++) {
    SER = d >> 7;
    d <<= 1;
    SRCLK = 0;
    delay(1);
    SRCLK = 1;
    delay(1);
  }
  RCLK_ = 0;
  delay(1);
  RCLK_ = 1;
}

// 每列为一个u8
static u8 matrix[8] = {0};

static u8 col = 0;   // 列号
static u8 line = 0;  // 行号
static u8 temp = 0;  // 临时数据

// 从矩阵中获取某一位的值
// 行号和列号都从0开始
// u8 get_matrix(u8 line, u8 col) {
//   return getBit(led_data[col], line);
// }

// 设置矩阵中某一位的值
// 行号和列号都从0开始
void setMatrix(u8 col, u8 line, u8 value) {
  if (value == 0)
    matrix[col] = clrBit(matrix[col], line);
  else
    matrix[col] = setBit(matrix[col], line);
}

// 矩阵全部置零
void clearMatrix() {
  for (temp = 0; temp < 8; temp++) {
    matrix[temp] = 0;
  }
}

// 将矩阵的数据更新
void updateMatrix() {
  for (col = 0; col < 8; col++) {
    P0 = colBuf[col];  // 选择列
    // 写入此列的数据
    write(matrix[col]);
    delay(100);
    write(0x00);
  }
}

// 方向
// 0上 1右 2下 3左
int direction = 0;

// 长度
int length = 3;

// 3个果实的坐标
u8 targets[3] = {0};

// 更新果实坐标
void updateTargets() {

}

// 坐标
// 第0位: 是否使用, 1为使用
// 234位: x坐标, 范围0-7
// 567位: y坐标, 范围0-7

// 从坐标int中取出x坐标(234位)
u8 getX(u8 location) {
  return (location >> 4) & 7; // 0111
}

// 从坐标int中取出y坐标(567位)
u8 getY(u8 location) {
  return location & 7; // 0111
}

// 判断此坐标是否使用
u8 isUse(u8 location) {
  return location >> 7;
}

// 设置此坐标为使用
u8 setUse(u8 location) {
  return setBit(location, 0);
}

// 设置此坐标为未使用
u8 clrUse(u8 location) {
  return setBit(location, 0);
}

int main() {
  int i = 0, j = 0;
  while (1) {
    for (i = 0; i < 8; i++) {
      clearMatrix();
      for (j = 0; j < 8; j++) {
        setMatrix((j + i) % 8, j, 1);
      }
      updateMatrix();
    }
  }

  return 0;
}
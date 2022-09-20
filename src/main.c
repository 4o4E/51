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

static u8 line_buf[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
// 列数据
static u8 col_buf[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

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
void set_matrix(u8 line, u8 col, u8 value) {
  if (value == 0)
    matrix[col] = clrBit(matrix[col], line);
  else
    matrix[col] = setBit(matrix[col], line);
}

// 矩阵全部置零
void clear_matrix() {
  for (temp = 0; temp < 8; temp++) {
    matrix[temp] = 0;
  }
}

// 将矩阵的数据更新
void update_matrix() {
  for (col = 0; col < 8; col++) {
    P0 = matrix[col];  // 选择列
    // 写入此列的数据
    write(matrix[col]);
    delay(10);
  }
}

int main() {
  int i = 0, j = 0;
  while (1) {
    LED0 = ~LED0;
    // for (i = 0; i < 8; i++) {
    //   for (j = 0; j < 8; j++) {
    //     P0 = col_buf[i];
    //     write(line_buf[j]);
    //     delay(10000);
    //   }
    // }
    clear_matrix();
    for (j = 0; j < 8; j++) {
      set_matrix(0, j, 1);
    }

    if (getBit(matrix[0], 0) == 1)
      LED7 = 1;
    else
      LED7 = 0;

    update_matrix();
    delay(100000);
  }

  return 0;
}
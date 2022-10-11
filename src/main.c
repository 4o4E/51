#include "STDLIB.H"
#include "reg52.h"

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
void setMatrix(u8 col, u8 line, bit value) {
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

// 随机数的种子
int seed = 1000, r = 0;

// 获取随机数
int getRandom(int from, int to) {
  srand(seed);
  r = rand();
  seed += r;
  seed %= 1000;
  return r % (to - from) + from;
}

// 方向
// 0左 1上 2下 3右
int direction = 0;

// 长度
int length = 3;

// 果实的坐标
u8 target = 0;

// 坐标
// 第0位: 是否使用, 1为使用
// 234位: x坐标, 范围0-7
// 567位: y坐标, 范围0-7

// 从坐标int中取出x坐标(234位)
u8 getX(u8 location) {
  return (location >> 4) & 0x01110000;  // 0111
}

// 向坐标int中写入x坐标
u8 setX(u8 location, u8 x) {
  return (u8)((location & 0x10001111) & ((x & 0x00000111) << 4));
}

// 从坐标int中取出y坐标(567位)
u8 getY(u8 location) {
  return location & 0x00001110;
}

// 向坐标int中写入y坐标
u8 setY(u8 location, u8 y) {
  return (u8)((location & 0x111110001) & ((y & 0x00000111) << 1));
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

// 更新果实坐标
void updateTarget() {
  setUse(target);
  setX(target, (u8)getRandom(0, 15));
  setY(target, (u8)getRandom(0, 15));
}

u8 body[64] = {0};

int t, lt, last, l, x, y;

// 蛇前进
void sneakForward() {
  for (t = 0; i < length; i++) {
    // 首个
    if (t == 0) {
      last = lt = body[t];
      x = getX(lt);
      y = getY(lt);
      // 判断是否吃到果实
      if (getX(target) == x && getY(target) == y) {
        length++;
      }

      // 0左 1上 2下 3右
      switch (direction) {
        case 0:
          x--;
          x %= 8;
          break;
        case 1:
          y++;
          y %= 8;
        case 2:
          y--;
          y %= 8;
        default:
          x++;
          x %= 8;
      }
      lt = setX(lt, x);
      lt = setY(lt, y);
      body[0] = lt;
      continue;
    }
    // 其他
    lt = body[t];
    body[t] = last;
    last = lt;
  }
}

bit l0 = 0, l1 = 0, l2 = 0, l3 = 0;

// 扫描按键确定方向
void scanDirection() {
  sacn();
  delay(500);
  sacn();
}

// 0左 1上 2下 3右
void scan() {
  // 左
  if (KEY0) {
    if (l0)
      direction = 0;
    else
      l0 = 1;
    return;
  }
  // 上
  if (KEY1) {
    if (l1)
      direction = 1;
    else
      l1 = 1;
    return;
  }
  // 下
  if (KEY2) {
    if (l2)
      direction = 2;
    else
      l2 = 1;
    return;
  }
  // 右
  if (KEY3) {
    if (l3)
      direction = 3;
    else
      l3 = 1;
  }
}

int main() {
  int i = 0, j = 0;
  while (1) {
    seed++;
    seed %= 1000;
    for (i = 0; i < 8; i++) {
      clearMatrix();  // 清空矩阵
      if (~isUse(target))
        updateTarget();  // 若未设置目标, 则重新设置
      setMatrix(getX(target), getY(target));  // 点亮果实位置
      for (j = 0; j < 8; j++) {
        setMatrix((j + i) % 8, j, 1);
      }
      updateMatrix();
    }
  }

  return 0;
}
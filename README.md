### 流水灯

> LED亮起一盏从左至右循环闪烁

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

typedef unsigned long int u16;

void delay(u16 us) {
  while (us--) {
  }
}

int main() {
  int i;

  while (1) {
    for (i = 0; i < 8; i++) {
      P2 = ~(0x01 << i);
      delay(1000);
    }
  }

  return 0;
}
```

</details>

### 流水灯作业

> 1. 向右循环闪烁
> 2. 向左循环闪烁
> 3. 奇偶闪烁
> 4. 从中间向两边扩散

<details>
  <summary>点击查看代码</summary>

```c
#include "STDLIB.H"
#include "reg51.h"
#include "intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;

void delay(u16 us) {
  while (us--) {
  }
}

u8 arr[8] = {
  231,
  219,
  189,
  126,
};

int i = 0, j = 0;

int main() {
  for (i = 0; i < 4; i++) {
    P2 = arr[i];
    delay(20000);
  }
  P2 = 0xfe;
  delay(20000);
  for (i = 0; i < 7; i++) {
    P2 = _crol_(P2, 1);
    delay(20000);
  }
  for (i = 0; i < 7; i++) {
    P2 = _cror_(P2, 1);
    delay(20000);
  }
  P2 = 85;
  delay(20000);
  P2 = ~P2;
  delay(20000);
  return 0;
}
```

</details>

### 蜂鸣器

> 响一下

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

// 蜂鸣持续时长
#define DURATION 100
// 总持续时长
#define AT 1000
// 高电位持续时长
#define HT 1

typedef unsigned int u16;

sbit BEEP = P2 ^ 5;

void delay(u16 us) {
  while (us--) {
  }
}

int main() {
  u16 i = DURATION;
  while (1) {
    while (i--) {
      BEEP = 0;
      delay(AT - HT);
      BEEP = 1;
      delay(HT);
    }
    i = 0;
    BEEP = 0;
  }
  return 0;
}
```

</details>

### 静态数码管

> 数码管第一位循环显示0-f

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

u8 gsmg_code[17] = {
    0x3f,
    0x06,
    0x5b,
    0x4f,
    0x66,
    0x6d,
    0x7d,
    0x07,
    0x7f,
    0x6f,
    0x77,
    0x7c,
    0x39,
    0x5e,
    0x79,
    0x71};

void delay(u16 us) {
  while (us--) {
  }
}

int main() {
  int i;
  while (1) {
    for (i = 0; i < 17; i++) {
      P0 = gsmg_code[i];
      delay(10000);
    }
  }
  return 0;
}
```

</details>

### 动态数码管

> 数码管显示`01234567`

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u8 gsmg_code[17] = {
    0x3f,
    0x06,
    0x5b,
    0x4f,
    0x66,
    0x6d,
    0x7d,
    0x07,
    0x7f,
    0x6f,
    0x77,
    0x7c,
    0x39,
    0x5e,
    0x79,
    0x71};

void delay(u16 us) {
  while (us--) {
  }
}

void smg_display() {
  u8 i = 0;
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
    P0 = gsmg_code[i];
    delay(100);
  }
}

int main() {
  while (1) {
    smg_display();
  }
  return 0;
}
```

</details>

### 数码管作业1

> 按下独立按键第一位显示6, 松开显示8

<details>
  <summary>点击查看代码</summary>

```c
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
```

</details>

### 数码管作业2

> 全部数码管循环显示`2`, `4`, `6`, `8`

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;

u8 gsmg_code[17] = {0x5b, 0x66, 0x7d, 0x7f};

void delay(u16 us) {
  while (us--) {
  }
}

int main() {
  int i, j, k;
  while (1) {
    for (i = 0; i < 4; i++) {
      for (j = 0; j < 10; j++) {
        for (k = 0; k < 8; k++) {
          // 设置数码管位数
          switch (k) {
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
          P0 = gsmg_code[i];
          delay(100);
        }
        delay(100);
      }
    }
  }
  return 0;
}
```

</details>

### 独立按键

> 按下独立按键亮起对应led, 支持多按键检测

<details>
  <summary>点击查看代码</summary>

```c
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
```

</details>

### 独立按键 & LED灯作业

> 1. 按下第1个按键切换LED循环左移
> 2. 按下第2个按键切换LED循环右移
> 3. 按下第3个按键切换LED奇偶闪烁
> 4. 按下第4个按键切换LED关闭

<details>
  <summary>点击查看代码</summary>

```c
#include "intrins.h"
#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit KEY0 = P3 ^ 1;
sbit KEY1 = P3 ^ 0;
sbit KEY2 = P3 ^ 2;
sbit KEY3 = P3 ^ 3;

void delay(u16 us) {
  while (us--) {
  }
}

// 状态
// 0 循环左移
// 1 循环右移
// 2 奇偶闪烁
// 3 灯灭
int state = 3, change = 0, tmp = 0;

int main() {
  int l0 = 0, l1 = 0, l2 = 0, l3 = 0;

  while (1) {
    if (KEY0 == 0) {
      if (l0 == 0)
        state = 0, change = 1;
      else
        l0 = 0;
      goto sign;
    }

    if (KEY1 == 0) {
      if (l1 == 0)
        state = 1, change = 1;
      else
        l1 = 0;
      goto sign;
    }

    if (KEY2 == 0) {
      if (l2 == 0)
        state = 2, change = 1;
      else
        l2 = 0;
      goto sign;
    }

    if (KEY3 == 0) {
      if (l3 == 0)
        state = 3, change = 1;
      else
        l3 = 0;
      goto sign;
    }
  sign:;
    if (++tmp >= 20) {
      tmp = 0;
      switch (state) {
        case 0:  // 循环左
          if (change)
            P2 = 0x0FE, change = 0;
          P2 = _cror_(P2, 1);
          break;
        case 1:
          if (change)
            P2 = 0xFE, change = 0;
          P2 = _crol_(P2, 1);
          break;
        case 2:
          if (change)
            P2 = 0xAA, change = 0;
          P2 = _cror_(P2, 1);
          break;
        case 3:
          P2 = 0xFF, change = 0;
          break;
      }
    }
    delay(500);
  }

  return 0;
}
```

</details>

### 矩阵按键

> 按下几个矩阵按键, LED屏就显示几(0-f)

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

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
```

</details>

### 8x8矩阵流水灯

> LED矩阵从左至右从上到下亮起一盏循环闪烁

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit SRCLK = P3 ^ 6;
sbit RCLK_ = P3 ^ 5;
sbit SER = P3 ^ 4;

sbit LED = P2 ^ 0;

u8 line_buf[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
// 列数据
u8 col_buf[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

void delay(u16 us) {
  while (us--) {
  }
}

void write_(u8 d) {
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

int main() {
  int i = 0, j = 0;
  while (1) {
    LED = ~LED;
    for (i = 7; i >= 0; i--) {
      for (j = 0; j < 8; ++j) {
        P0 = col_buf[j];
        write_(line_buf[i]);
        delay(10000);
      }
    }
  }

  return 0;
}
```

</details>

### 8x8矩阵动态

> LED矩阵斜向循环闪烁

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

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
```

</details>

### 贪吃蛇 未完成

> 小demo, 未完成

<details>
  <summary>点击查看代码</summary>

```c
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
          --x %= 8;
          break;
        case 1:
          --y %= 8;
        case 2:
          ++y %= 8;
        default:
          ++x %= 8;
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
// 0左 1上 2下 3右
// 需要delay 50后再执行一次
void scanDirection() {
  if (KEY0) {
    if (l0) {
      direction = 0;
      return;
    } else
      l0 = 1;
  }

  if (KEY1) {
    if (l1) {
      direction = 1;
      return;
    } else
      l1 = 1;
  }

  if (KEY2) {
    if (l2) {
      direction = 2;
      return;
    } else
      l2 = 1;
  }

  if (KEY3) {
    if (l3) {
      direction = 3;
      return;
    } else
      l3 = 0;
  }
}

int main() {
  int i = 0, j = 0;
  LED1 = ~LED1;
  updateTarget();  // 更新果实位置
  LED2 = ~LED2;
  while (1) {
    LED3 = ~LED3;
    seed++;
    seed %= 1000;
    scanDirection();
    delay(50);
    scanDirection();
    sneakForward();
    for (i = 0; i < 1000; i++) {
      LED1 = ~LED1;
      clearMatrix();                          // 清空矩阵
      setMatrix(getX(target), getY(target));  // 点亮果实位置
      for (j = 0; j < 8; j++) {
        matrix[j] = body[j];
      }
      updateMatrix();
    }
  }

  return 0;
}
```

</details>

### 中断作业

> 利用外部中断按键 S1 控制 P2 口 8 个 LED 灯，中断时使 8 个 LED 灯闪 烁 10 次

<details>
  <summary>点击查看代码</summary>

```c
#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit KEY3 = P3 ^ 2;
sbit KEY4 = P3 ^ 3;
sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;

void delay(u16 us) {
  while (us--) {
  }
}

void init0() {
  IT0 = 1;
  EX0 = 1;
  EA = 1;
}

static int i;

void exti0() interrupt 0 {
  delay(1000);
  if (KEY3 == 0) {
    for (i = 0; i < 10; i++)
    {
      P2 = 0;
      delay(10000);
      P2 = 0xff;
      delay(10000);
    }
  }
}

int main() {
  init0();
  while(1);
  return 0;
}
```

</details>

### 中断作业2

> 使用外部中断0和外部中断1，按键接单片机的P3.2和P3.3引脚（下降沿有效），当响应外部中断0时，驱动4位集成的数码管动态扫描方法显示1 4 9 2（循环5次），当响应外部中断1时，驱动8只LED灯奇数灯与偶数灯交叉闪烁（循环5次）

<details>
  <summary>点击查看代码</summary>

```c
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
```

</details>

### 定时器作业

> 采用定时器T0工作方式1控制LED亮65ms灭65ms，循环闪烁

<details>
  <summary>点击查看代码</summary>

```c
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
```

</details>

### 定时器作业2

> 已知系统晶振12MHz，采用定时器T0的工作方式1实现延时，控制P2口的8只发光二极管以50ms的间隔循环点亮。

<details>
  <summary>点击查看代码</summary>

```c
#include "intrins.h"
#include "reg51.h"

typedef unsigned char u8;
typedef unsigned int u16;

void init0() {
  TMOD |= 0X01;            // 选择为定时器0模式 工作方式1
  TH0 = 0XFC, TL0 = 0X18;  // 给定时器赋初值 定时1ms
  ET0 = 1;                 // 打开定时器0中断允许
  EA = 1;                  // 打开总中断
  TR0 = 1;                 // 打开定时器
}

u8 i;  //定义静态变量i

void exti0() interrupt 1 {
  TH0 = 0XFC, TL0 = 0X18;  // 给定时器赋初值，定时1ms
  i++;
  if (i == 50) {
    i = 0;
    P2 = _crol_(P2, 1);
  }
}

int main() {
  init0();
  P2 = 0xfe;
  while (1) {
  }
  return 0;
}
```

</details>

### 期中作业

> 按下矩阵按键的第一个按键, 播放`当那一天来临`

<details>
  <summary>点击查看代码</summary>

```c
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
```

</details>
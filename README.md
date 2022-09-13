### 流水灯

```c
#include "reg52.h"

typedef unsigned long int u16;

void delay(u16 us)
{
  while (us--)
  {
  }
}

int main()
{
  int i;

  while (1)
  {
    for (i = 0; i < 8; i++)
    {
      P2 = ~(0x01 << i);
    }
  }

  return 0;
}
```

### 蜂鸣器

```c
#include "reg52.h"

// 蜂鸣持续时长
#define DURATION 100
// 总持续时长
#define AT 1000
// 高电位持续时长
#define HT 1

typedef unsigned int u16;

sbit BEEP = P2 ^ 5;

void delay(u16 us)
{
    while (us--)
    {
    }
}

int main()
{
    u16 i = DURATION;
    while (1)
    {
        while (i--)
        {
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

### 静态数码管

```c
#include "reg52.h"

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

void delay(u16 us)
{
  while (us--)
  {
  }
}

int main()
{
  int i;
  while (1)
  {
    for (i = 0; i < 17; i++)
    {
      P0 = gsmg_code[i];
      delay(10000);
    }
  }
  return 0;
}
```

### 动态数码管

```c
#include "reg52.h"

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

void delay(u16 us)
{
  while (us--)
  {
  }
}

void smg_display()
{
  u8 i = 0;
  for (i = 0; i < 8; i++)
  {
    // 设置数码管位数
    switch (i)
    {
      case 0: LSC = 1; LSB = 1; LSA = 1; break;
      case 1: LSC = 1; LSB = 1; LSA = 0; break;
      case 2: LSC = 1; LSB = 0; LSA = 1; break;
      case 3: LSC = 1; LSB = 0; LSA = 0; break;
      case 4: LSC = 0; LSB = 1; LSA = 1; break;
      case 5: LSC = 0; LSB = 1; LSA = 0; break;
      case 6: LSC = 0; LSB = 0; LSA = 1; break;
      case 7: LSC = 0; LSB = 0; LSA = 0; break;
    }
    // 设置显示
    P0 = gsmg_code[i];
    delay(100);
  }
}

int main()
{
  while (1)
  {
    smg_display();
  }
  return 0;
}
```

### 独立按键

```c
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

sbit LED7 = P2 ^ 7;

void delay(u16 us)
{
  while (us--)
  {
  }
}

int main()
{
  int l0 = 0,
      l1 = 0,
      l2 = 0,
      l3 = 0;

  while (1)
  {
    if (KEY0 == 0)
    {
      if (l0 == 0)
        LED0 = 0;
      else
        l0 = 0;
    }
    else
    {
      if (l0 == 1)
        LED0 = 1;
      else
        l0 = 1;
    }

    if (KEY1 == 0)
    {
      if (l1 == 0)
        LED1 = 0;
      else
        l1 = 0;
    }
    else
    {
      if (l1 == 1)
        LED1 = 1;
      else
        l1 = 1;
    }
    
    if (KEY2 == 0)
    {
      if (l2 == 0)
        LED2 = 0;
      else
        l2 = 0;
    }
    else
    {
      if (l2 == 1)
        LED2 = 1;
      else
        l2 = 1;
    }
    
    if (KEY3 == 0)
    {
      if (l3 == 0)
        LED3 = 0;
      else
        l3 = 0;
    }
    else
    {
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

### 矩阵按键

```c
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
    LED7 = ~LED7;
  }
  return 0;
}
```

### 
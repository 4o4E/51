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
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int get_bit(unsigned char *a, int index) {
  return (a[index >> 3] >> (7 - (index & 7))) & 1;
}

void set_bit(unsigned char *a, int index) {
  int mask = sizeof(char) - 1;
  a[index] |= 1 << (mask - (index & mask));
}

void clear_bit(unsigned char *a, int index) {
  int mask = sizeof(char) - 1;
  a[index] &= ~(1 << (mask - (index & mask)));
}

int sum(int a, int b, int mod) {
  unsigned int i, j, r, d, kA, mA, sA, kB, mB, sB;
  unsigned int min, max;
  unsigned long long sumA = 0, sumB = 0, countA = 0, countB = 0;
  unsigned int len = a * b;
  unsigned char *sumedA, *sumedB;
  unsigned char bitA, bitB;

  if(a > b) {
    min = b;
    max = a;
  } else {
    min = a;
    max = b;
  }
  sumedA = (unsigned char*)malloc(len / sizeof(char) + 1);
  memset(sumedA, 0, len / sizeof(char) + 1);
  sumedB = (unsigned char*)malloc(max * 2 / sizeof(char));
  memset(sumedB, 0, max * 2 / sizeof(char));

  for(i = 1; i <= min; ++i) {
    for(j = i; j <= max; ++j) {
      kA = i * j;
      mA = kA >> 3;
      sA = 7 - kA & 7;
      bitA = sumedA[mA] >> sA;
      if((bitA & 1) == 0) {
        sumA = (sumA + kA);
        sumedA[mA] |= 1 << sA;
        ++countA;
      }

      kB = i ^ j;
      mB = kB >> 3;
      sB = 7 - kB & 7;
      bitB = sumedB[mB] >> sB;
      if((bitB & 1) == 0) {
        sumB = (sumB + kB);
        sumedB[mB] |= 1 << sB;
        ++countB;
      }
    }
  }
  sumB *= countA;
  r = b;
  d = 10;
  while(r > 0) {
    d *= 10;
    r /= 10;
  }
  sumA = sumA * d * countB;

  printf("\n[%d - %d]:", len, countA);
  /*for(i = 1; i <= len; ++i) {
    if(get_bit(sumedA, i))
      printf("%d ", i);
  }*/
  printf("\n[%d - %d]:", max * 2, countB);
  /*for(i = 0; i <= max * 2; ++i) {
    if(get_bit(sumedB, i))
      printf("%d ", i);
  }*/
  printf("\n");

  return (sumA + sumB) % mod ;
}

int run (int a,int b)
{
    return sum(a, b, 1000000007);
}

int main(int argc, char **argv)
{    
    printf("%d",run(atoi(argv[1]), atoi(argv[2])));
}

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

int get_bit(unsigned char *a, int index) {
  return (a[index >> 3] >> (7 - (index & 7))) & 1;
}

void set_bit(unsigned char *a, int index) {
  int mask = sizeof(char) * 8 - 1;
  a[index] |= 1 << (mask - (index & mask));
}

void clear_bit(unsigned char *a, int index) {
  int mask = sizeof(char) * 8 - 1;
  a[index] &= ~(1 << (mask - (index & mask)));
}

int sum(int a, int b, int mod) {
  unsigned int i, j, r, d, kA, kB, t;
  unsigned int min, max;
  unsigned long long sumA = 0, sumB = 0, countA = 0, countB = 0;
  unsigned int len = a * b;
  unsigned char *sumedA, *sumedB;
  unsigned char bitA, bitB;
  unsigned char *pA, *pB;

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

  countA = max;
  countB = max;
  sumA = (max + 1) * max / 2;
  sumB = sumA;
  pA = sumedA;
  pB = sumedB;
  t = max / 8;
  for(i = 0; i < t; ++i) {
    *pA++ = ~0;
    *pB++ = ~0;
  }

  for(i=0; i <= max - t * 8; ++i) {
    sumedA[t] |= 1 << (7 - ((t * 8 + i) & 7));
    sumedB[t] |= 1 << (7 - ((t * 8 + i) & 7));
  }
  sumedA[0] &= ~(1 << (7 - (0 & 7)));
  sumedB[0] &= ~(1 << (7 - (1 & 7)));
  if((max % 2) == 1) {
    sumB = sumB - 1;
  } else {
    sumedB[max >> 3] &= ~(1 << (7 - (max & 7)));
    sumedB[(max + 1) >> 3] |= 1 << (7 - ((max + 1) & 7));
  }
  //printf("A[0]: %x\n", sumedA[0]);
  //printf("B[0]: %x\n", sumedB[0]);

  for(i = 2; i <= min; ++i) {
    t = i * i;
    kA = t;
    for(j = i; j <= max; ++j) {
      if(((sumedA[kA >> 3] >> (7 - (kA & 7))) & 1) == 0) {
        sumA = (sumA + kA);
        sumedA[kA >> 3] |= 1 << (7 - kA & 7);
        ++countA;
      }
      kA += i;

      kB = i ^ j;
      if(((sumedB[kB >> 3] >> (7 - (kB & 7))) & 1) == 0) {
        sumB = (sumB + kB);
        sumedB[kB >> 3] |= 1 << (7 - (kB & 7));
        ++countB;
      }
    }
  }
  //printf("sumA=%d, sumB=%d\n", sumA, sumB);
  sumB *= countA;
  r = b;
  d = 10;
  while(r > 0) {
    d *= 10;
    r /= 10;
  }
  sumA = sumA * d * countB;
  /*printf("sumA=%d, sumB=%d\n", sumA, sumB);

  printf("\n[%d - %d]:", len, countA);
  for(i = 1; i <= len; ++i) {
    if(get_bit(sumedA, i))
      printf("%d ", i);
  }
  printf("\n[%d - %d]:", max * 2, countB);
  for(i = 0; i <= max * 2; ++i) {
    if(get_bit(sumedB, i))
      printf("%d ", i);
  }
  printf("\n");*/

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

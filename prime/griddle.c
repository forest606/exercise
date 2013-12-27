#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int prime (int num)
{
  long c = 7;
  int maxc;

  if (num == 2 || num == 3 || num == 5)
    return 1;
  if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0)
    return 0;

  maxc = (int)sqrt(num);
  while (c <= maxc)
    {
      if (num % c == 0)
        return 0;
      c += 4;
      if (num % c == 0)
        return 0;
      c += 2;
      if (num % c == 0)
        return 0;
      c += 4;
      if (num % c == 0)
        return 0;
      c += 2;
      if (num % c == 0)
        return 0;
      c += 4;
      if (num % c == 0)
        return 0;
      c += 6;
      if (num % c == 0)
        return 0;
      c += 2;
      if (num % c == 0)
        return 0;
      c += 6;
    }
  return 1;
}

void list_prime(int num) {
  int count = 1;
  int i = 1;
  int n = 2 * i + 1;
  printf("2");
  while(n <= num) {
    if(prime(n)) {
      printf(", %d", n);
      ++count;
    }
    n += 2;
  }
  printf("\nTotal: %d\n", count);
}

int main(int argc, char **argv) {
  int n;
  n = atoi(argv[1]);
  list_prime(n);
  return 0;
}

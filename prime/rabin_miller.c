#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int prime(long long num);
int witness(int n, long long num);

void test_prime(long long n) {
    if( prime(n) )
        printf("Yes, it is a prime number.\n");
    else
        printf("No, it isn't a prime number.\n");
}

void list_prime(long n) {
  int i, base = 30; // 2 * 3 * 5
  int mod[] = {1, 7, 11, 13, 17, 19, 23, 29};
  int len = sizeof(mod)/sizeof(int);
  long count = 24;
  long index = 60, num;
  //printf("2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89\n");
  while(index <= n) {
    index += base;
    for(i = 0; i < len; ++i) {
      num = index + mod[i];
      if(num > n)
        break;
      if(prime(num)) {
        //printf("%ld\n", num);
        ++count;
      }
    }
  }
  printf("prime count [2 -- %ld]: %ld\n", n, count);
}

void sum_prime(long n) {
  int i, base = 30; // 2 * 3 * 5
  int mod[] = {1, 7, 11, 13, 17, 19, 23, 29};
  int len = sizeof(mod)/sizeof(int);
  long count = 24;
  long index = 30000000, num, sum = 963;
  //printf("2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89\n");
  while(index <= n) {
    for(i = 0; i < len; ++i) {
      num = index + mod[i];
      if(num > n)
        break;
      if(prime(num)) {
        //printf("%ld\n", num);
        ++count;
        sum = (sum + num) % 1000000007;
      }
    }
    index += base;
  }
  printf("prime count [2 -- %ld]: %ld\n", n, count);
  printf("prime sum [2 -- %ld]: %ld\n", n, sum);
}

int main(int argc, char **argv)
{
    long n = atol(argv[1]);
    sum_prime(n);
    //list_prime(n);
    //test_prime(n);
    return 0;
}

int prime(long long num)
{
    //int arr[3] = {19,71,97};
    int arr[3] = {2,7,61};
    int i;
    if(2 == num)
        return 1;
    if(1==num || 0==num&1)
        return 0;
    for(i=0;i<3;i++)
    {
        if( witness(arr[i], num) )
            return 0;
    }
    return 1;
}

int witness(int a,long long n)
{
    long long j, m, x0, x1, b, i;
    m = n-1;
    j = 0;
    while(m%2 == 0)
    {
        m /= 2;
        j++;
    }
    b = a;
    x0 = 1;
    while(m)
    {
        if(m%2)
            x0 = x0 * b % n;
        m /= 2;
        b = b * b % n;
    }
    for(i=0;i<j;i++)
    {
        x1 = x0 * x0 % n;
        if(x1==1 && x0!=1 && x0!=n-1)
            return 1;
        x0 = x1;
    }
    if(x0 != 1)
        return 1;
    return 0;
}

#ifndef MEISSEL_LEHMER_H
#define MEISSEL_LEHMER_H
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define CACHE_M 7

//Pi(n),小于n的素数个数，即查表
long long pi(long long n);
//Phi(x, n), 小于x与p(1)...p(n)互素的数的个数
long long phi(long long x, long long n, long long m);
//小于n的素数个数，用于不在素数表中的大数
long long primeBelow(long long n);
//在low 和 up 之间查找第index个素数
long long __prime( long long low, long long up, long long index);
//初始化素数表和Phi(x, CACHE_M)表
void initPrimeArray(long long n);
//查找第index个素数
long long prime(long long index);
//删除建立的表
void collect( void );

#endif // MEISSEL_LEHMER_H

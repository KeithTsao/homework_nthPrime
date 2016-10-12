#include "meissel_lehmer.h"

long long *arr_prime;//小于n^(2/3)的素数表
long long *table_phi, *preset_table_phi;//
long long q, p;
long long preset_p, preset_q;
char *mark;
long long count;

//Pi(n),小于n的素数个数
long long pi(long long n)
{
    if(n <= 2) return 0;
    long long i = 0, mark = 0;
    unsigned long long up, low, mid;

    low = 0;
    up = count - 1;
    while(low < up - 1)
    {
        mid = (low + up)/2;
        if(arr_prime[mid] < n)
        {
            low = mid;
        }
        else
        {
            up = mid;
        }
    }
    return low + 1;
}

//Phi(x,n), 表示小于x与前n个素数互素的数的个数
long long phi(long long x, long long n, long long m)
{
    if (n == m)
    {
        return (x / q) * p + table_phi[x % q];
    }
    if (x < arr_prime[n - 1])
    {
        return 1;
    }
    return phi(x, n - 1, m) - phi(x / arr_prime[n - 1], n - 1, m);
}

//这个函数是放大版的pi(n)
long long primeBelow(long long n)
{
    long long i, j, m = CACHE_M;
    long long sum = 0, s = 0;
    long long len, len2, len3;

    if (n < 10000)
    {
        return pi(n);
    }

    //n^(1/3)内的素数数目
    len = pi((long long)exp(1.0 / 3 * log(n)));
    //n^(1/2)内的素数数目
    len2 = pi((long long)sqrt(n));
    //n^（2/3)内的素数数目
    len3 = pi((long long)exp(2.0 / 3 * log(n)) - 1);

    //乘积个数
    j =(long long)exp(2.0 / 3 * log(n)) - 2;
    for (i = (long long)exp(1.0 / 3 * log(n)); i <= (long long)sqrt(n); ++i)
    {
        if (!mark[i])
        {
            while (i * j > n)
            {
                {
                    if (!mark[j])
                    {
                        ++s;
                    }
                    --j;
                }
            }
            sum += s;
        }
    }
    sum = (len2 - len) * len3 - sum;
    sum += (len * (len - 1) - len2 * (len2 - 1)) / 2;

    //欧拉函数
    if (m > len)//n不够大时（导致 ）使用临时表
    {
        m = len;
        p = 1, q = 1;
        for (i = 0; i < m; ++i)
        {
            q *= arr_prime[i];
            p *= arr_prime[i] - 1;
        }
        table_phi = (long long *)malloc(sizeof(long long) * q);
        for (i = 0; i < q; ++i)
        {
            table_phi[i] = i;
        }
        for (i = 0; i < m; ++i)
        {
            for (j = q - 1; j >= 0; --j)
            {
                table_phi[j] -= table_phi[j / arr_prime[i]];
            }
        }
        sum = phi(n, len, m) - sum + len - 1;
        free(table_phi);
    }
    else//在n足够大时使用预初始化的表
    {
        table_phi = preset_table_phi;
        p = preset_p;
        q = preset_q;
        sum = phi(n, len, m) - sum + len - 1;
    }

    return sum;
}

//二分查找
long long __prime( long long low, long long up, long long index)
{
    if(up - low <= 2) return low;
    long long mid = ((up + low) / 2) | 0x01;
    long long n;

    n = primeBelow(mid);
    if(n < index)
    {
        return __prime(mid + 2, up, index);
    }
    else
    {
        return __prime(low, mid, index);
    }
}

void initPrimeArray(long long n)
{
    long long mark_len;
    long long i, j;

    count = 0;
    mark_len = (n < 10000) ? 10002 : ((long long)exp(2.0 / 3 * log(n)) + 1);

    //筛选n^(2/3)或n内的素数
    mark = (char *)malloc(sizeof(char) * mark_len);
    memset(mark, 0, sizeof(char) * mark_len);
    for (i = 2; i < (long long)sqrt(mark_len); ++i)
    {
        if (mark[i])
        {
            continue;
        }
        for (j = i + i; j < mark_len; j += i)
        {
            mark[j] = 1;
        }
    }
    mark[0] = mark[1] = 1;

    //统计素数数目
    for (i = 0; i < mark_len; ++i)
    {
        if (!mark[i])
        {
            ++count;
        }
    }

    //保存素数
    arr_prime = (long long *)malloc(sizeof(long long) * count);
    j = 0;
    for (i = 0; i < mark_len; ++i)
    {
        if (!mark[i])
        {
            arr_prime[j++] = i;
        }
    }


    //Phi(x, CACHE_M)表，利用递推式Phi(x, m) = Phi(x, m - 1) - Phi(x / p(m), m - 1)
    //p(m)表示第m个素数
    long long m = CACHE_M;
    p = q = 1;
    for (i = 0; i < m; ++i)
    {
        q *= arr_prime[i];
        p *= arr_prime[i] - 1;
    }
    preset_table_phi = (long long *)malloc(sizeof(long long) * q);
    for (i = 0; i < q; ++i)
    {
        preset_table_phi[i] = i;
    }
    for (i = 0; i < m; ++i)
    {
        for (j = q - 1; j >= 0; --j)
        {
            preset_table_phi[j] -= preset_table_phi[j / arr_prime[i]];
        }
    }
    preset_p = p, preset_q = q;

    return;
}

long long prime(long long index)
{

    long long up, low;
    long long ans;

    if(index <= 100)
    {
        initPrimeArray(600);
        ans = arr_prime[index+1];
        collect();
        return ans;
    }

    up = (long long)(index * log(index) + index * log(log(index)));
    low = up - index;
    low = (low - 1) | 0x01;
    initPrimeArray(up);
    ans = __prime(low, up, index);
    collect();
    return ans;
}

void collect( void )
{
    free (preset_table_phi);
    free (mark);
    free (arr_prime);
    return;
}

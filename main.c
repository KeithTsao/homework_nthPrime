#include <stdio.h>
#include "meissel_lehmer.h"

#define MAX_LEN 10
#define MAX_NUM 100000000

int main()
{
    long long n;
    long long count;
    if(1 != scanf("%lld", &n))
    {
        printf("Error!\n");
        return 0;
    }
    if(n > MAX_NUM)
    {
        printf("Error!\n");
        return 0;
    }
    count = prime(n);
    printf("%lld\n", count);
    return 0;
}

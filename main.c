#include <stdio.h>
#include "meissel_lehmer.h"

int main()
{
    long long n;
    long long count;
    while(scanf("%lld", &n) != EOF)
    {  
        count = prime(n);
        printf("%lld\n", count);
    }
    return 0;
}

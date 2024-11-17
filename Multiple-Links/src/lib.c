
#include <stdio.h>

static char hello_1 = 0;
static short int hello_2 = 0;
static int hello_3 = 0;
static unsigned long hello_4 = 0;
static unsigned long long hello_5 = 0;

void lib_func(void)
{
    hello_1++;
    hello_1 += hello_2;
    hello_2 += hello_3;
    hello_3 += hello_4;
    hello_4 += hello_5;
}

void lib_print(void)
{
    printf("lib addr: 0x%016x size: %d -> %d\n", &hello_1, sizeof(hello_1), hello_1);
    printf("lib addr: 0x%016x size: %d -> %d\n", &hello_2, sizeof(hello_2), hello_2);
    printf("lib addr: 0x%016x size: %d -> %d\n", &hello_3, sizeof(hello_3), hello_3);
    printf("lib addr: 0x%016x size: %d -> %d\n", &hello_4, sizeof(hello_4), hello_4);
    printf("lib addr: 0x%016x size: %d -> %d\n", &hello_5, sizeof(hello_5), hello_5);
}

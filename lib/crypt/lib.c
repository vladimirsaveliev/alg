#include <stdio.h>

struct mi_struct
{
    int q;
    int a;
    int b;
    int r;
    int t1;
    int t2;
    int t;
};

/*
 * multiplicative inverse
 * a > b
 */
int mi(int a, int b)
{
    struct mi_struct mi;
    
    mi.a = a;
    mi.b = b;
    mi.t1 = 0;
    mi.t2 = 1;
    
    printf("%4s%4s%4s%4s%4s%4s%4s\n", "Q", "A", "B", "R", "T1", "T2", "T");
    while (mi.b != 0) {
        /* calculate q, r, t */
        mi.q = mi.a / mi.b;
        mi.r = mi.a % mi.b;
        mi.t = mi.t1 - mi.t2 * mi.q;
        printf("%4d%4d%4d%4d%4d%4d%4d\n", mi.q, mi.a, mi.b, mi.r, mi.t1, mi.t2, mi.t);
        
        /* shift */
        mi.a = mi.b;
        mi.b = mi.r;
        mi.t1 = mi.t2;
        mi.t2 = mi.t;
    }
    return mi.t1;
}

/*
 * multiple and square algorithm
 */
int mod_power(int base, int power, int modulo)
{
    int prod;
    int p;
    int i;
    
    prod = 1;
    p = base;
    for (i = 0; i < sizeof(power) * 8; i++) {
        p %= modulo;
        if (power & (1 << i)) {
            prod *= p;
            prod %= modulo;
            printf("%x: p = %d prod %d\n", 1 << i, p, prod);
        }
        p *= p;
    }
    return prod % modulo;
}
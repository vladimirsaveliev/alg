#include <stdio.h>

/*
 * multiplicative inverse
 */

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
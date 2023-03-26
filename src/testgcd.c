#include <config.h>
#include <stdio.h>
#include "lib/discrete-math/discrete-math.h"

int testgcd(void)
{
	int a;
	int b;

	printf("Enter numbers: ");
	scanf(" %d %d", &a, &b);
	printf("%d %d %d\n", a, b, gcd(a,b));

	printf("gcd(%d, %d) as linear combination of %d and %d\n", a, b, a, b);
	gcd2(a, b);

	return 0;
}

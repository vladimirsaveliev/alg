#include <stdio.h>

int gcd(int r_n, int r_n_plus_1)
{
	int r_n_plus_2;

	if (r_n_plus_1 == 0)
		return r_n;
	r_n_plus_2 = r_n % r_n_plus_1;
	return  gcd(r_n_plus_1, r_n_plus_2);
}


/* express gcd as linear combination of a and b */
void gcd2(int r_n, int r_n_plus_1)
{
	int r_n_plus_2;
	int q;

	if (r_n_plus_1 == 0) {
		printf("%d", r_n);
		return;
	}

	q = r_n / r_n_plus_1;
	r_n_plus_2 = r_n % r_n_plus_1;
	if (r_n_plus_2)
		printf("%d = %d * %d + %d => %d = %d - %d * %d\n", r_n, q, r_n_plus_1, r_n_plus_2,
		       r_n_plus_2, r_n, q, r_n_plus_1);
	gcd2(r_n_plus_1, r_n_plus_2);
	printf(" = %d - %d * %d\n", r_n, q * r_n_plus_1, r_n_plus_2);
}

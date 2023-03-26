#include <stdio.h>
#include "../lib/crypt/crypt.h"

int testcrypt(void)
{
	while (1) {
		char c;

		printf("   \x1b[37;1m1 - modulo power\x1b[0m\n");
		printf("   \x1b[37;1m2 - multiplicative inverse\x1b[0m\n");
		printf("   0 - return to main menu\n");

		scanf(" %c", &c);
		switch (c) {
                    case '1': {
                        int b, p, m;
                        
			printf("      base power module: ");
			if (scanf(" %d %d %d", &b, &p, &m) != 3) {
                            printf("valid input example: 10 20 30\n");
                            continue;
                        }
                        printf("res %d\n", mod_power(b, p, m));
			break;
                    }
                    case '2': {
                        int a, b;
                        
			printf("      big small: ");
			if (scanf(" %d %d", &a, &b) != 2 || a <= b) {
                            printf("valid input example: 20 15\n");
                            continue;
                        }
                        printf("res %d\n", mi(a, b));
                        break;
                    }
                    case '0':
			return 0;
		}
	}
}


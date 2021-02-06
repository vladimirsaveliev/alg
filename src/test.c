#include <config.h>
#include <stdio.h>
#include <stdlib.h>

int testbst(void);

int main(void)
{
	printf(PACKAGE_STRING"\n");

	while (1) {
		char c;

		printf("1 - test BST\n");
		printf("2 - test AVL tree\n");
		printf("0 - quit\n");
		scanf(" %c", &c);
		switch (c) {
		case '1':
			testbst();
			break;
		case '2':
			printf("not ready\n");
			break;
		case '0':
			exit(0);
		}
	}
	return 0;
}

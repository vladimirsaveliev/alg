// #include <config.h>
#include <stdio.h>
#include <stdlib.h>

int testbst(void);
int testavl(void);
int testgcd(void);
int test2darray(void);
int testsortable_array(void);
int testdigraph(void);
int testgraph(void);
void hash_function();

int main(void)
{
//	printf(PACKAGE_STRING"\n");

	while (1) {
		char c;

		printf("1 - test BST\n");
		printf("2 - test AVL tree\n");
		printf("3 - greatest common divisor\n");
		printf("4 - array\n");
		printf("5 - sortable array\n");
		printf("6 - graph\n");
		printf("7 - digraph\n");
		printf("8 - hash fucntion\n");
		printf("0 - quit\n");
		scanf(" %c", &c);
		switch (c) {
		case '1':
			testbst();
			break;
		case '2':
			testavl();
			break;
		case '3':
			printf("not ready\n");
			break;
/*			testgcd();
			break;*/
		case '4':
			printf("not ready\n");
			break;
/*			test2darray();
			break;*/
		case '5':
			testsortable_array();
			break;
		case '6':
			testgraph();
			break;
		case '7':
			testdigraph();
			break;
		case '8':
			hash_function();
			break;
		case '0':
			exit(0);
		}
	}
	return 0;
}

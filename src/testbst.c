#include <config.h>
#include <stdio.h>
#include "lib/bst/bst.h"

#if 1
void build_pb_bst(struct bst_node **root,  int *keys, int nr_keys)
{
	int ind = nr_keys / 2;

	if (nr_keys == 0)
		return;
	bst_insert(root, keys[ind]);
	build_pb_bst(root, keys, ind);
	build_pb_bst(root, keys + ind + 1, nr_keys - ind - 1);
}
#endif

/*
 *
 */
int testbst(void)
{
	struct bst_node *root;

	root = NULL;
	while (1) {
		char c;
		int key;

		printf("   \x1b[37;1m1 - insert element\x1b[0m\n");
		printf("   2 - delete element\n");
		printf("   3 - print BST\n");
		printf("   0 - return to main menu\n");

		scanf(" %c", &c);
		switch (c) {
		case '1':
			printf("      key to insert: ");
			scanf(" %d", &key);
			bst_insert(&root, key);
			break;
		case '2':
			printf("delete\n");
			break;
		case '3':
			printf("\x1B[36;1m");
			bst_show_tree(root);
			printf("\x1b[0m");
			break;
		case '0':
			bst_destroy(root);
			return 0;
		}
	}
#if 0
/*	int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};*/
	int data[7] = {1, 2, 3, 4, 5, 6, 7};
/*	int data[5] = {2, 1, 3, 9, 7};*/
	int i;

	printf(PACKAGE_STRING"\n");


	root = NULL;

/*	build_pb_bst(&root, data, sizeof(data)/sizeof(data[0]));*/

	for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
		bst_insert(&root, data[i]);
	}

/*
	bst_insert(&root, -1);
	bst_insert(&root, -3);
	bst_insert(&root, -2);
*/
	bst_show_tree(root);


	{
		/* test predecessor */
		struct bst_node *p;
		int key;

		for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
			key = data[i];
			p = bst_predecessor(root, key, NULL);
			printf("key %d -> pred %d\n", key, p ? p->key : 5555555);
		}
	}


	bst_destroy(root);
#endif
	return 0;
}

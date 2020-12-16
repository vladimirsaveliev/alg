#include <config.h>
#include <stdio.h>
#include "lib/bst/bst.h"

/*
 *
 */
int main(void)
{
	struct bst_node *root;
/*	int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};*/
	int data[5] = {1, 2, 3, 4, 5};
/*	int data[5] = {2, 1, 3, 9, 7};*/
	int i;

	printf(PACKAGE_STRING"\n");


	root = NULL;
	for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
		bst_insert(&root, data[i]);
	}
	bst_insert(&root, -1);
	bst_insert(&root, -3);
	bst_insert(&root, -2);

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
	return 0;
}

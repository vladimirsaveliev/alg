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
	int data[5] = {2, 1, 3, 9, 7};
	int i;

	printf(PACKAGE_STRING"\n");


	root = NULL;
	for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
		bst_insert(&root, data[i]);
	}

	bst_show_tree(root);

	bst_destroy(root);
	return 0;
}

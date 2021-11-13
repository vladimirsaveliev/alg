#include <config.h>
#include <stdio.h>
#include <malloc.h>
#include "lib/bst/avl.h"

#if 0
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
int testavl(void)
{
	struct avl_node *root;

	root = NULL;
	while (1) {
		char c;
		int key;

		printf("   \x1b[37;1m1 - insert element\x1b[0m\n");
		printf("   2 - delete element\n");
		printf("   3 - print AVL\n");
		printf("   0 - return to main menu\n");

		scanf(" %c", &c);
		switch (c) {
		case '1':
			printf("      key to insert: ");
			scanf(" %d", &key);
			avl_insert(&root, key);

            printf("\x1B[36;1m");
            avl_show_tree(root);
			printf("\x1b[0m");
            break;
		case '2':
#if 0
			printf("      key to delete: ");
			scanf(" %d", &key);
			bst_delete(&root, key);

			printf("\x1B[36;1m");
			bst_show_tree(root);
			printf("\x1b[0m");
#endif
            printf("not ready\n");
			break;

		case '3':
			printf("\x1B[36;1m");
			avl_show_tree(root);
			printf("\x1b[0m");
			break;

		case '0':
			avl_destroy(root);
			return 0;
		}
	}
}

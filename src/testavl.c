// #include <config.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "../lib/bst/avl.h"

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
void build_pb_avl(struct avl_node **root,  int *keys, int nr_keys)
{
	int i;
	
	if (nr_keys == 0)
		return;
	for (i = 0; i < nr_keys; i++) {
		avl_insert(root, keys[i]);
	}

}

/*
 *
 */
int testavl(void)
{
	struct avl_node *root;
	int i;
	int nr;

	root = NULL;
	while (1) {
		char c;
		int key;

		printf("   \x1b[37;1m1 - insert element\x1b[0m\n");
		printf("   2 - delete element\n");
		printf("   3 - print AVL\n");
		printf("   4 - insert array\n");
		printf("   5 - build random tree\n");
		printf("   0 - return to main menu\n");

		scanf(" %c", &c);
		switch (c) {
		case '1':
			printf("      key to insert: ");
			scanf(" %d", &key);
			avl_insert(&root, key);

			avl_show_tree(root);
			break;
		case '2':
			printf("      key to delete: ");
			scanf(" %d", &key);
			i = avl_delete(&root, key);
			printf("avl_delete(%d) rc=%d\n", key, i);

			avl_show_tree(root);
			break;

		case '3':
			avl_show_tree(root);
			break;

		case '4': {
			int *arr;

			printf("      number of keys: ");
			scanf(" %d", &nr);
			arr = malloc(sizeof(int) * nr);
			if (arr == NULL) {
				perror("malloc failed");
				break;
			}
			for (i = 0; i < nr; i++) {
				scanf(" %d", &arr[i]);
			}
			build_pb_avl(&root, arr, nr);
			free(arr);

			avl_show_tree(root);
			break;
		}
		case '5':
			printf("      number of keys: ");
			scanf(" %d", &nr);
			for (i = 0; i < nr; i++) {
				avl_insert(&root, rand() % 999);
			}
			avl_show_tree(root);
			break;
			
		case '0':
			avl_destroy(root);
			return 0;
		}
	}
}

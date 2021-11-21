#include <config.h>
#include <stdio.h>
#include <malloc.h>
#include "lib/bst/bst.h"

/*
Q
Q3
   Proof by MI
      Case for n = 1
      K1,2 can be ordered so that it has only one topological ordering
      For example:
             2
	  <-
      1	   
          ->
             3
     Such graph has single TO: 2->1->3
     Assume that Kn and n + 1 can be ordered so it has only one TO
     Prove that Kn+1,n+2 has only one TO
     Assume we add vertex a to left partition and b to the right vertex group.
     Then direct all edges of vertex a to vertex a but edge a b.
     Direct all edges of vertex b to vertex b, then the single topological ordering of Kn,n+1 will be appended with a and b
     Then Kn+1,n+2 has a single topological ordering.
     
Q4 
   Sorted2bst(root v, keys[], nr_keys) {
         if nr_key = 0 then
	      return
         medium := nr_keys / 2
	 BSTInstert(v, keys[medium])
	 Sorted2bst(v, keys, medium)
	 Sorted2bst(v, keys + medium + 1, nr_keys - medium - 1)
}



 */

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
	struct bst_node *tmp;

	root = NULL;
	while (1) {
		char c;
		int key;

		printf("   \x1b[37;1m1 - insert element\x1b[0m\n");
		printf("   2 - delete element\n");
		printf("   3 - print BST\n");
		printf("   4 - built tree by array\n");
		printf("   5/6 - min/max\n");
		printf("   0 - return to main menu\n");

		scanf(" %c", &c);
		switch (c) {
		case '1':
			printf("      key to insert: ");
			scanf(" %d", &key);
			bst_insert(&root, key);

			printf("\x1B[36;1m");
			bst_show_tree(root);
			printf("\x1b[0m");
			break;
		case '2':
			printf("      key to delete: ");
			scanf(" %d", &key);
			bst_delete(&root, key);

			printf("\x1B[36;1m");
			bst_show_tree(root);
			printf("\x1b[0m");
			break;

		case '3':
			printf("\x1B[36;1m");
			bst_show_tree(root);
			printf("\x1b[0m");
			break;

		case '4': {
			int nr;
			int *arr;
			int i;

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
			build_pb_bst(&root, arr, nr);
			free(arr);

			printf("\x1B[36;1m");
			bst_show_tree(root);
			printf("\x1b[0m");
			break;
		}
		case '5':
			tmp = bst_min(root);
			printf("min key: %d\n", tmp->key);
			break;
		case '6':
			tmp = bst_max(root);
			printf("max key: %d\n", tmp->key);
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

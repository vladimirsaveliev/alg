#if HAVE_MALLOC_H
#include <malloc.h>
#endif
#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

#include "bst.h"
#include "../array/array.h"

int bst_insert(struct bst_node **root, int key)
{
	if (*root == NULL) {
		*root = malloc(sizeof(struct bst_node));
		if (*root == NULL)
			BST_FATAL("malloc failed");
		(*root)->key = key;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return BST_INSERT_OK;
	}

	if ((*root)->key == key)
		return BST_INSERT_EXIST;

	if ((*root)->key > key) {
		return bst_insert(&((*root)->left), key);
	} else {
		return bst_insert(&((*root)->right), key);
	}
}

struct bst_node *bst_find(struct bst_node *root, int key)
{
	if (root == NULL)
		return NULL;
	if (root->key == key)
		return root;
	if (root->key > key)
		return bst_find(root->left, key);
	else
		return bst_find(root->right, key);
}

/*
 *         3
 *    2        4
 * predecessor for 4 is 3
 */
/*
 *
Input:
	v - root node of binary search tree
	k - key to look a preceding key of
	predecessor - tree node containg the biggest key smaller than key x

Output:
	predecessor - tree node containg the biggest key smaller than key x

Usage:
	predecessor = 0
	v = root
	predecessor = BSTPredecessor(v, k, precessor)

Data types
	struct node
		left - pointer to node
		right - pointer to node
		key k
	key
		int

BSTPredecessor(node v, key x, node predecessor)
	if v == 0
		return predecessor

	if x == k(v)
		// predecessor is the rightmost node of left subtree (if left subtree exists
		tmp = l(v)
		while tmp
			predecessor = tmp
			tmp = r(tmp)
		return predecessor

	if (x < k(v))
		return BSTPredecessir(l(v), x, predecessor)
	else
		// go to right, save new predecessor
		predecessor = v
		return BSTPredecessor(r(v), x, predecessor)
 *
 */
struct bst_node *bst_predecessor(struct bst_node *root, int key, struct bst_node *pred)
{
	if (root == NULL)
		return pred;

	if (root->key == key) {
		struct bst_node *tmp;

		tmp = root->left;
		while (tmp) {
			pred = tmp;
			tmp = tmp->right;
		}
		return pred;
	}

	if (root->key > key) {
		return bst_predecessor(root->left, key, pred);
	} else {
		pred = root;
		return bst_predecessor(root->right, key, pred);
	}
}

#if 0
struct bst_node *bst_delete(struct bst_node **root, int key)
{
	if (*root == NULL)
		return BST_DELETE_NOTFOUND;

	if (key < (*root)->key) {
		return bst_delete(&((*root)->left), key);
	}
	if (key > (*root)->key) {
		return bst_delete(&((*root)->right), key);
	}
	if ((*root)->left == NULL && (*root)->right == NULL) {
		*root = NULL;
		return BST_DELETE_OK;
	}
	if ((*root)->left == NULL) {
	}
	if ((*root)->right == NULL) {
	}
}
#endif

void bst_destroy(struct bst_node *root)
{
	if (root == NULL)
		return;
	bst_destroy(root->left);
	bst_destroy(root->right);
	free(root);
}

int bst_depth(struct bst_node *root, int depth)
{
	int ld;
	int rd;

	if (root == NULL)
		return depth;
	depth++;
	ld = bst_depth(root->left, depth);
	rd = bst_depth(root->right, depth);
	return (ld > rd) ? ld : rd;
}

static void bst_fill_level(struct bst_node *root, struct int_array *arr,
			   int level, int cur_level)
{
	if (root == NULL) {
		int n, i;

		n = 1 << (level - cur_level - 1);
		for (i = 0; i < n; i++)
			array_push_back(arr, INT_MIN);
		return;
	}
	cur_level++;
	if (cur_level == level) {
		array_push_back(arr, root->key);
		return;
	}
	bst_fill_level(root->left, arr, level, cur_level);
	bst_fill_level(root->right, arr, level, cur_level);	
}

void bst_show_line(struct bst_node *root)
{
	if (root == NULL)
		return;
	bst_show_line(root->left);
	printf("%4d", root->key);
	bst_show_line(root->right);
}

/*
 * print nodes on specified level
 */
static void _show_level(struct bst_node *root, int level, int width)
{
	struct int_array arr;

	array_init(&arr, 1 << level);

	bst_fill_level(root, &arr, level, -1);

	array_print(&arr, width);
	array_free(&arr);
}

void bst_show_tree(struct bst_node *root)
{
	int depth;
	int i;
	int leaf_width = 4; /* width for the lowest leaf */

	depth = bst_depth(root, -1);
	if (depth == -1) {
		printf("tree is empty\n");
		return;
	}

	for (i = 0; i <= depth; i++) {
		_show_level(root, i, leaf_width * (1 << (depth - i)));
	}
}

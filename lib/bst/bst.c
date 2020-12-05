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

#if HAVE_MALLOC_H
#include <malloc.h>
#endif
#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

#include "bst.h"
#include "../array/array.h"

/*
 * insert key into tree
 */
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

// Algorithm with no recursion
// Return value:
//         pointer to element of tree
struct bst_node* bst_predecessor2(struct bst_node* root, int key)
{
	struct bst_node *pred = NULL;  // pointer to predecessor

	while (root->key != key) {
		if (root->key > key) {
			if (root->left == NULL) {
				return NULL; // key is not found
			}
			root = root->left;
			continue;
		} else {
			// key > root->key
			if (root->right == NULL) {
				return NULL;
			}
			pred = root;
			root = root->right;
		}
		
	}
	// Key is found here
	if (root->left == NULL) {
//		return pred;
	} else {
		root = root->left;
		while (root->right != NULL) {
			root = root->right;
		}
		pred = root;
	}

	
	return pred;
}

/*
struct bst_node* BST_successor(struct bst_node *root, int key)
{
	struct bst_node* success = NULL;
	if (root->right != NULL) {
		root = root->right;
		while(root->left != NULL) {
			success = root->left;
		}
		return success;
	}
	

}
*/


void bst_split(struct bst_node *root, int key)
{
	struct bst_node *parent = NULL;
	struct bst_node *child = root;
	
	while (child->key != key) {
		parent = child;
		if (child->key > key) {
			if (child->left == NULL) {
				printf("%d not found\n", key);
				return;
			}
			child = child->left;
		}
		else {
			if (child->right == NULL) {
				printf("%d not found\n", key);
			        return;
			}
			child = child->right;
		}
	}
	// key is found
	if (parent == NULL) {
		struct bst_node *T1 = child->left;
		struct bst_node *T2 = child;
		child->left = NULL;
		printf("T1:\n");
		bst_show_tree(T1);
		printf("T2:\n");
		bst_show_tree(T2);
		return;
	}
	if (parent->left == child) {
		struct bst_node *T1 = child->left;
		struct bst_node *T2 = root;
		child->left = NULL;
		printf("T1:\n");
		bst_show_tree(T1);
		printf("T2:\n");
		bst_show_tree(T2);
		return;
	}
	if (parent->right == child) {
		struct bst_node *T1 = root;
		parent->right = child->left;
		struct bst_node *T2 = child;
		child->left = NULL;
		printf("T1:\n");
		bst_show_tree(T1);
		printf("T2:\n");
		bst_show_tree(T2);
		return;
	}
	printf("Unknown case\n");
}

/* AG1, lecture 6, p. 9 */
struct bst_node *bst_min(struct bst_node *v)
{
    if (v->left == NULL) {
        return v;
    }
    return bst_min(v->left);
}

struct bst_node *bst_max(struct bst_node *v)
{
	if(v->right == NULL) {
		return v;
	}
	return bst_max(v->right);
}

/*
 * AG1, lecture 6, p. 14
 */
int bst_delete(struct bst_node **root, int key)
{
    struct bst_node *s;

	if (*root == NULL) {
        /* empty root */
		return BST_DELETE_NOTFOUND;
    }
	if (key < (*root)->key) {
		return bst_delete(&((*root)->left), key);
	}
	if (key > (*root)->key) {
		return bst_delete(&((*root)->right), key);
	}
	if ((*root)->left == NULL && (*root)->right == NULL) {
        /* no children */
		*root = NULL;
		return BST_DELETE_OK;
	}
	if ((*root)->left == NULL) {
        /* only right child */
        *root = (*root)->right;
        return BST_DELETE_OK;
	}
	if ((*root)->right == NULL) {
        /* only left child */
        *root = (*root)->left;
        return BST_DELETE_OK;
	}
	/* two children */
    s = bst_min((*root)->right);
    (*root)->key = s->key;
    bst_delete(&((*root)->right), s->key);
    return BST_DELETE_OK;
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

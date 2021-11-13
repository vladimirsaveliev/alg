/*
 * AG1, lecture 6
 * AVL - depth balanced trees
 */

#include "stdio.h"
#include "stdlib.h"
#include "limits.h"

#include "avl.h"
#include "../array/array.h"

void right_rotate(struct avl_node *x)
{
    struct avl_node tmp;
    struct avl_node *y;
    
    y = x->left;
    
    /*
     *           |                 |
     *           x                 y
     *         /   \      ->     /   \
     *       y       C         A       x
     *     /   \                     /   \
     *   A       B                 B       C
     */
    tmp = *x;
    x->key = y->key;
    x->left = y->left;
    x->right = y;
                        
    y->key = tmp.key;
    y->left = y->right;
    y->right = tmp.right;
}

void left_rotate(struct avl_node *x)
{
    struct avl_node tmp;
    struct avl_node *y;
    
    y = x->right;
    
    /*
     *           |                  |
     *           x                  y
     *         /   \      ->      /   \
     *       A      y            x      C
     *            /   \        /   \
     *           B     C     A       B
     */
    tmp = *x;
    
    x->key = y->key;
    x->right = y->right;
    x->left = y;
    
    y->key = tmp.key;
    y->right = y->left;
    y->left = tmp.left;
}

/*
 * insert key into tree
 */
int avl_insert(struct avl_node **root, int key)
{
    int rc;
    struct avl_node *x;
    struct avl_node *y;
    struct avl_node tmp;
    
	if (*root == NULL) {
		*root = malloc(sizeof(struct avl_node));
		if (*root == NULL)
			AVL_FATAL("malloc failed");
		(*root)->key = key;
		(*root)->left = NULL;
		(*root)->right = NULL;
        (*root)->disbalance = same_depth;
		return AVL_INSERT_OK;
	}

	if ((*root)->key == key)
		return AVL_INSERT_EXIST;

	if ((*root)->key > key) {
		rc = avl_insert(&((*root)->left), key);
        if (rc != AVL_CONTINUE_PROPAGATION)
            return AVL_INSERT_OK;
        /* from left child */
        switch ((*root)->disbalance) {
            case right_greater:
                /* case 1 */
                (*root)->disbalance = same_depth;
                /* propagation stops */
                rc = AVL_STOP_PROPAGATION;
                break;

            case same_depth:
                /* case 2 */
                (*root)->disbalance = left_greater;
                /* propagation continues */
                rc = AVL_CONTINUE_PROPAGATION;
                break;
                
            case left_greater:
                /* case 3 */
                /* rebalance is required */
                x = (*root);
                y = (*root)->left;
                switch (y-> disbalance) {
                    case left_greater: /* 3a */
                        right_rotate(x);
                        break;
                        
                    case right_greater: /* 3b */
                        left_rotate(y);
                        right_rotate(x);
                        break;
                        
                    case same_depth: /* 3c */
                        AVL_FATAL("should not happen");
                }
                rc = AVL_STOP_PROPAGATION;
                break;
                
                
            default:
                AVL_FATAL("unknown disbalance");
        }
	} else {
		rc = avl_insert(&((*root)->right), key);
        if (rc != AVL_CONTINUE_PROPAGATION)
            return AVL_INSERT_OK;
        /* from right child */
        switch ((*root)->disbalance) {
            case left_greater:
                /* case 1 */
                (*root)->disbalance = same_depth;
                /* propagation stops */
                rc = AVL_STOP_PROPAGATION;
                break;

            case same_depth:
                /* case 2 */
                (*root)->disbalance = right_greater;
                /* propagation continues */
                rc = AVL_CONTINUE_PROPAGATION;
                break;
                
            case right_greater:
                /* case 3 */
                /* rebalance is required */
                x = (*root);
                y = (*root)->right;
                switch (y-> disbalance) {
                    case right_greater: /* 3a */
                        left_rotate(x);
                        break;
                        
                    case left_greater: /* 3b */
                        right_rotate(y);
                        left_rotate(x);
                        break;
                        
                    case same_depth: /* 3c */
                        AVL_FATAL("should not happen");
                }
                rc = AVL_STOP_PROPAGATION;
                break;                
                
            default:
                AVL_FATAL("unknown disbalance");
        }
	}
	return rc;
}

void avl_destroy(struct avl_node *root)
{
	if (root == NULL)
		return;
	avl_destroy(root->left);
	avl_destroy(root->right);
	free(root);
}

int avl_depth(struct avl_node *root, int depth)
{
	int ld;
	int rd;

	if (root == NULL)
		return depth;
	depth++;
	ld = avl_depth(root->left, depth);
	rd = avl_depth(root->right, depth);
	return (ld > rd) ? ld : rd;
}

static void avl_fill_level(struct avl_node *root, struct int_array *arr,
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
	avl_fill_level(root->left, arr, level, cur_level);
	avl_fill_level(root->right, arr, level, cur_level);	
}

void avl_show_line(struct avl_node *root)
{
	if (root == NULL)
		return;
	avl_show_line(root->left);
	printf("%4d", root->key);
	avl_show_line(root->right);
}

/*
 * print nodes on specified level
 */
static void _show_level(struct avl_node *root, int level, int width)
{
	struct int_array arr;

	array_init(&arr, 1 << level);

	avl_fill_level(root, &arr, level, -1);

	array_print(&arr, width);
	array_free(&arr);
}

void avl_show_tree(struct avl_node *root)
{
	int depth;
	int i;
	int leaf_width = 4; /* width for the lowest leaf */

	depth = avl_depth(root, -1);
	if (depth == -1) {
		printf("tree is empty\n");
		return;
	}

	for (i = 0; i <= depth; i++) {
		_show_level(root, i, leaf_width * (1 << (depth - i)));
	}
}


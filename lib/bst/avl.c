/*
 * AG1, lecture 6
 * AVL - depth balanced trees
 */

#include "stdio.h"
#include "stdlib.h"
#include "limits.h"
#include "string.h"

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
	x->disbalance = same_depth;
                        
	y->key = tmp.key;
	y->left = y->right;
	y->right = tmp.right;
	y->disbalance = same_depth;
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
	x->disbalance = same_depth;
    
	y->key = tmp.key;
	y->right = y->left;
	y->left = tmp.left;
	y->disbalance = same_depth;
}


/*
 * insert key into tree
 */
int avl_insert(struct avl_node **root, int key)
{
	int rc;
	struct avl_node *x;
	struct avl_node *y;
	struct avl_node *z;
    
	if (*root == NULL) {
		*root = malloc(sizeof(struct avl_node));
		if (*root == NULL)
			AVL_FATAL("malloc failed");
		(*root)->key = key;
		(*root)->left = NULL;
		(*root)->right = NULL;
		(*root)->disbalance = same_depth;
		return AVL_CONTINUE_PROPAGATION;
	}

	if ((*root)->key == key)
		return AVL_INSERT_EXIST;

	if ((*root)->key > key) {
		/* left child */
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
				/* R
				 */
				x->left = y->right;
				y->right = x;
				(*root) = y;
				x->disbalance = y->disbalance = same_depth;
				break;
		    
			case right_greater: /* 3b */
				z = y->right;
				/* L
				 */
				y->right = z->left;
				z->left = y;
				x->left = z;

				/* R
				 */
				x->left = z->right;
				z->right = x;

				if (z->disbalance == left_greater) {
					y->disbalance = same_depth;
					x->disbalance = right_greater;
				} else if (z->disbalance == right_greater) {
					y->disbalance = left_greater;
					x->disbalance = same_depth;
				} else {
					y->disbalance = same_depth;
					x->disbalance = same_depth;
				}
				
				z->disbalance = same_depth;
				(*root) = z;
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
				/* L
				 */
				x->right = y->left;
				y->left = x;
				(*root) = y;
				x->disbalance = y->disbalance = same_depth;
				break;
                        
			case left_greater: /* 3b */
				z = y->left;
				/* R
				 */
				y->left = z->right;
				z->right = y;
				x->right = z;

				/* L
				 */
				x->right = z->left;
				z->left = x;

				if (z->disbalance == right_greater) {
					y->disbalance = same_depth;
					x->disbalance = left_greater;
				} else if (z->disbalance == left_greater) {
					y->disbalance = right_greater;
					x->disbalance = same_depth;
				} else {
					y->disbalance = same_depth;
					x->disbalance = same_depth;
				}
				
				z->disbalance = same_depth;
				(*root) = z;
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

/* AG1, lecture 6, p. 9 */
const struct avl_node *avl_min(const struct avl_node *v)
{
    if (v->left == NULL) {
        return v;
    }
    return avl_min(v->left);
}

#if 0
/*
 * AG1, lecture 6, p. 36
 */
static left_delete_rebalance(struct avl_node *x, enum disbalance_coefficient was) {
	if (x->disbalance == left_greater) {
		/* case 1 */
		x->disbalance = same_depth;
		return AVL_CONTINUE_PROPAGATION;
	}
	if (x->disbalance == same_depth) {
		/* case 2 */
		x->disbalance = right_greater;
		return AVL_STOP_PROPAGATION;
	}
}
#endif

/*
 * AG1, lecture 6, p. 35
 */
int avl_delete(struct avl_node **root, int key)
{
	int rc;
	const struct avl_node *s;
	struct avl_node *x;
	struct avl_node *y;
	struct avl_node *z;

	if (*root == NULL) {
		/* empty root */
		return AVL_DELETE_NOTFOUND;
	}
	
	if (key < (*root)->key) {
		/* left child */
		rc = avl_delete(&((*root)->left), key);
		if (rc != AVL_CONTINUE_PROPAGATION)
			return AVL_DELETE_OK;
		/* from left child */
		switch ((*root)->disbalance) {
		case left_greater:
			/* case 1 */
			(*root)->disbalance = same_depth;
			rc = AVL_CONTINUE_PROPAGATION;
			break;
			
		case same_depth:
			/* case 2 */
			(*root)->disbalance = right_greater;
			rc = AVL_STOP_PROPAGATION;
			break;
			
		case right_greater:
			/* case 3 */
			/* rebalance is required */
			x = (*root);
			y = (*root)->right;
			switch (y->disbalance) {
			case right_greater: /* 3a */
				/* left rotate */
				x->right = y->left;
				y->left = x;
				x->disbalance = same_depth;
				y->disbalance = same_depth;
				(*root) = y;
				rc = AVL_CONTINUE_PROPAGATION;
				break;

			case same_depth: /* 3b */
				/* left rotate */
				x->right = y->left;
				y->left = x;
				x->disbalance = right_greater;
				y->disbalance = left_greater;
				(*root) = y;
				rc = AVL_STOP_PROPAGATION;
				break;

			case left_greater: /* 3c */
				z = y->left;
				/* R
				 *      x                   x
				 *    /   \               /   \
				 *  A       y           A       z
				 *        /   \               /   \
				 *      z       D           B       y
				 *    /   \                       /   \
				 *  B       C                   C       D
				 */
				x->right = z;
				y->left = z->right;
				z->right = y;
				
				/* L
				 *      x                      z
				 *    /   \                  /   \
				 *  A       z              x       y
				 *        /   \          /   \   /   \
				 *      B       y      A      B C     D
				 *            /   \
				 *          C       D
				 */
				x->right = z->left;
				z->left = x;				
				if (z->disbalance == right_greater) {
					x->disbalance = same_depth;
					y->disbalance = left_greater;
				} else if (z->disbalance == left_greater) {
					x->disbalance = right_greater;
					y->disbalance = same_depth;
				} else {
					x->disbalance = y->disbalance = z->disbalance = same_depth;
				}
				
				z->disbalance = same_depth;
				(*root) = z;				
				rc = AVL_CONTINUE_PROPAGATION;
				break;
			}
			
			break;
		}
		
		return rc;
	}
	
	if (key > (*root)->key) {
		/* right child */
		rc = avl_delete(&((*root)->right), key);
		if (rc != AVL_CONTINUE_PROPAGATION)
			return AVL_DELETE_OK;
		/* from right child */
	from_right_child:
		switch ((*root)->disbalance) {
		case right_greater:
			/* case 1 */
			(*root)->disbalance = same_depth;
			rc = AVL_CONTINUE_PROPAGATION;
			break;
			
		case same_depth:
			/* case 2 */
			(*root)->disbalance = left_greater;
			rc = AVL_STOP_PROPAGATION;
			break;
			
		case left_greater:
			/* case 3 */
			/* rebalance is required */
			x = (*root);
			y = (*root)->left;
			switch (y->disbalance) {
			case left_greater: /* 3a */
				/* right rotate */
				x->left = y->right;
				y->right = x;
				x->disbalance = same_depth;
				y->disbalance = same_depth;
				(*root) = y;
				rc = AVL_STOP_PROPAGATION;
				break;
				
			case same_depth: /* 3b */
				/* right rotate */
				x->left = y->right;
				y->right = x;
				x->disbalance = left_greater;
				y->disbalance = right_greater;
				(*root) = y;
				rc = AVL_STOP_PROPAGATION;
				break;
				
			case right_greater: /* 3c */
				z = y->right;
				/* L
				 */
				x->left = z;
				y->right = z->left;
				z->left = y;

				/* R
				 */
				x->left = z->right;
				z->right = x;
				if (z->disbalance == left_greater) {
					x->disbalance = same_depth;
					y->disbalance = right_greater;
				} else if (z->disbalance == right_greater) {
					x->disbalance = left_greater;
					y->disbalance = same_depth;
				} else {
					x->disbalance = y->disbalance = z->disbalance = same_depth;
				}
				z->disbalance = same_depth;
				(*root) = z;				
				rc = AVL_CONTINUE_PROPAGATION;
				break;
			}

			break;
		}
		
		return rc;
	}
	
	if ((*root)->left == NULL && (*root)->right == NULL) {
		/* no children */
		*root = NULL;
		return AVL_CONTINUE_PROPAGATION;
	}
	if ((*root)->left == NULL) {
		/* only right child */
		*root = (*root)->right;
		return AVL_CONTINUE_PROPAGATION;
	}
	if ((*root)->right == NULL) {
		/* only left child */
		*root = (*root)->left;
		return AVL_CONTINUE_PROPAGATION;
	}

	/* two children */
	s = avl_min((*root)->right);
	(*root)->key = s->key;
//	(*root)->disbalance = s->disbalance;
	rc = avl_delete(&((*root)->right), s->key);
	if (rc != AVL_CONTINUE_PROPAGATION)
		return AVL_DELETE_OK;
	goto from_right_child;
}

void avl_destroy(struct avl_node *root)
{
	if (root == NULL)
		return;
	avl_destroy(root->left);
	avl_destroy(root->right);
	free(root);
}

static int avl_depth(struct avl_node *root, int depth)
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

/*
 * idx - current index in arr
 */
static void avl_fill_level(struct avl_node *root, struct avl_node **arr,
			   int level, int cur_level, int *idx)
{
	if (root == NULL) {
		int n, i;

		n = 1 << (level - cur_level - 1);
		for (i = 0; i < n; i++) {
			arr[*idx] = NULL;
			(*idx)++;
		}
		return;
	}
	cur_level++;
	if (cur_level == level) {
		arr[*idx] = root;
		(*idx)++;
		return;
	}
	avl_fill_level(root->left, arr, level, cur_level, idx);
	avl_fill_level(root->right, arr, level, cur_level, idx);	
}

static struct avl_node** array2_init(int size)
{
	struct avl_node **arr;

	arr = (struct avl_node **)malloc(sizeof(struct avl_node *) * size);
	if (arr == NULL)
		AVL_FATAL("malloc failed");
	return arr;
}

static char *disbalance(struct avl_node *node)
{
	if (node->disbalance == same_depth)
		return "S";
	if (node->disbalance == right_greater)
		return "R";
	return "L";
}

static void print2_center_aligned(struct avl_node *node, int width)
{
	int pre;
	int past;
	char p[12]; /* 2147483648 is 11 bytes long */
	char format[256];

	if (node == NULL) {
		printf("%*c", width, ' ');
		return;
	}
	
	sprintf(p, "%d(%s)", node->key, disbalance(node));
	pre = (width - strlen(p)) / 2;
	past = width - pre - strlen(p);

	sprintf(format, "%%%ds%%s%%%ds", pre, past);
	printf(format, "", p, "");
}

/*
 * size - num of elements in array
 * width - width of field
 */
static void array2_print(struct avl_node **arr, int size, int width)
{
	int i;
	
	for (i = 0; i < size; i++) {
		print2_center_aligned(arr[i], width);
	}
	printf("\n");
}

/*
 * print nodes on specified level
 */
static void _show_level(struct avl_node *root, int level, int width)
{
	struct avl_node **arr;
	int idx;

	arr = array2_init(1 << level);

	idx = 0;
	avl_fill_level(root, arr, level, -1, &idx);

	array2_print(arr, idx, width);
	free(arr);
}

void avl_show_tree(struct avl_node *root)
{
	int depth;
	int i;
	int leaf_width = 7; /* width for the lowest leaf: 4 for key and 3 for disbalance, etc (S) */

	printf("\x1B[36;1m");
	depth = avl_depth(root, -1);
	if (depth == -1) {
		printf("tree is empty\n");
		printf("\x1b[0m");
		return;
	}

	for (i = 0; i <= depth; i++) {
		_show_level(root, i, leaf_width * (1 << (depth - i)));
	}
	printf("\x1b[0m");
}

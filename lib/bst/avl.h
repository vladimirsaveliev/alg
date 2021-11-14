#pragma once

#define AVL_FATAL(msg) {			\
		perror(msg);			\
		exit(1);			\
	}


enum disbalance_coefficient {same_depth = 0, left_greater = -1, right_greater = 1};
	
struct avl_node {
	int key;
	struct avl_node *left;
	struct avl_node *right;
	enum disbalance_coefficient disbalance;
};


int avl_insert(struct avl_node **root, int key);
int avl_delete(struct avl_node **root, int key);
const struct avl_node *avl_min(const struct avl_node *root);

#define AVL_INSERT_OK 0
#define AVL_INSERT_EXIST 1
#define AVL_CONTINUE_PROPAGATION 2
#define AVL_STOP_PROPAGATION 3
#define AVL_DELETE_OK 0
#define AVL_DELETE_NOTFOUND 1

void avl_show_tree(struct avl_node *root);
void avl_destroy(struct avl_node *root);

#if 0
struct bst_node *bst_find(struct bst_node *root, int key);
void bst_show(struct bst_node *root);
int bst_depth(struct bst_node *root, int depth);
void bst_show_line(struct bst_node *root);

struct bst_node *bst_predecessor(struct bst_node *root, int key, struct bst_node *pred);
#endif

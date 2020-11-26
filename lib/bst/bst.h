#define BST_FATAL(msg) {			\
		perror(msg);			\
		exit(1);			\
	}

struct bst_node {
	int key;
	struct bst_node *left;
	struct bst_node *right;
};

int bst_insert(struct bst_node **root, int key);

#define BST_INSERT_OK 0
#define BST_INSERT_EXIST 1

struct bst_node *bst_find(struct bst_node *root, int key);
void bst_destroy(struct bst_node *root);
void bst_show(struct bst_node *root);
int bst_depth(struct bst_node *root, int depth);
void bst_show_line(struct bst_node *root);
void bst_show_tree(struct bst_node *root);



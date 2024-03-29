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
int bst_delete(struct bst_node **root, int key);
struct bst_node *bst_min(struct bst_node *root);
struct bst_node *bst_max(struct bst_node *root);

#define BST_INSERT_OK 0
#define BST_INSERT_EXIST 1
#define BST_DELETE_OK 0
#define BST_DELETE_NOTFOUND 1

struct bst_node *bst_find(struct bst_node *root, int key);
void bst_destroy(struct bst_node *root);
void bst_show(struct bst_node *root);
int bst_depth(struct bst_node *root, int depth);
void bst_show_line(struct bst_node *root);
void bst_show_tree(struct bst_node *root);

struct bst_node *bst_predecessor(struct bst_node *root, int key, struct bst_node *pred);
struct bst_node *bst_predecessor2(struct bst_node *root, int key);
void bst_split(struct bst_node *root, int key);

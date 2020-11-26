#define ARRAY_FATAL(msg) {			\
		perror(msg);			\
		exit(1);			\
	}

struct int_array {
	int *array;
	int max_size;
	int cur_size;
};

void array_init(struct int_array *arr, int max);
void array_push_back(struct int_array *arr, int max);
void array_free(struct int_array *arr);
void array_print(struct int_array *arr, int width);

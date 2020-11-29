#if HAVE_MALLOC_H
#include <malloc.h>
#endif
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"

#include "array.h"

void array_init(struct int_array *arr, int max)
{
	arr->array = malloc(sizeof(int) * max);
	if (arr->array == NULL)
		ARRAY_FATAL("malloc failed");
	arr->max_size = max;
	arr->cur_size = 0;
}

void array_push_back(struct int_array *arr, int val)
{
	if (arr->max_size == arr->cur_size)
		ARRAY_FATAL("out of array");
	arr->array[arr->cur_size] = val;
	arr->cur_size++;
}

void array_free(struct int_array *arr)
{
	free(arr->array);
}

static void print_center_aligned(int val, int width)
{
	int pre;
	int past;
	char p[12]; /* 2147483648 is 11 bytes long */
	char format[256];

	if (val == INT_MIN) {
		printf("%*c", width, ' ');
		return;
	}
	sprintf(p, "%d", val);
	pre = (width - strlen(p)) / 2;
	past = width - pre - strlen(p);

	sprintf(format, "%%%ds%%d%%%ds", pre, past);
	printf(format, "", val, "");
}

void array_print(struct int_array *arr, int width)
{
	int i;

	for (i = 0; i < arr->cur_size; i++) {
		if (width == 0)
			printf("%4d", arr->array[i]);
		else
			print_center_aligned(arr->array[i], width);
	}
	printf("\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "2d.h"

/**
 * Create 2d array \res and fill with \initvalue
 */
int create_2d(int rows, int cols, struct array_2d *res, int initvalue)
{
	int i;
	int j;

	res->rows = rows;
	res->cols = cols;
	res->array = (int **)malloc(rows * sizeof(int *));
	if (res->array == NULL)
		return -ENOMEM;
	for (i = 0; i < rows; i++) {
		res->array[i] = (int *)malloc(cols * sizeof(int));
		if (res->array[i] == NULL) {
			/* FIXME: free allocated memory */
			return -ENOMEM;
		}
		for (j = 0; j < cols; j++) {
			res->array[i][j] = initvalue;
		}
	}
	return 0;
}

/**
 * Read from \in and fill in \arr by rows
 */
int fill_2d(struct array_2d *arr)
{
	int i;
	int j;
	FILE *fp;
	int rows;
	int cols;
	char filename[256];

    printf("Enter num of rows and columns: ");
    scanf(" %d %d", &rows, &cols);
    getchar();

    printf("File with matrix %dx%d data: ", rows, cols);
    fgets(filename, 256, stdin);
    filename[strlen(filename) - 1] = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }
    create_2d(rows, cols, arr, 0);
	for (i = 0; i < arr->rows; i++) {
		for (j = 0; j < arr->cols; j++) {
			if (fscanf(fp, "%d", &arr->array[i][j]) != 1) {
			    printf("wrong data");
			    fclose(fp);
                return 1;
            }
		}
	}
	fclose(fp);
	return 0;
}

struct array_2d *multiply(const struct array_2d *m1, const struct array_2d *m2)
{
    struct array_2d *res;
    int i;
    int j;
    int k;

    if (m1->cols != m2->rows) {
        printf("can not multiply\n");
        return NULL;
    }
    res = malloc(sizeof(*res));
    if (res == NULL)
        return NULL;
    create_2d(m1->rows, m2->cols, res, 0);

    for (i = 0; i < res->rows; i++) {
        for (j = 0; j < res->cols; j++) {
            res->array[i][j] = 0;
            for (k = 0; k < m1->cols; k++)
                res->array[i][j] += m1->array[i][k] * m2->array[k][j];
        }
    }
    return res;
}

void print_2d(const struct array_2d *res)
{
	int i;
	int j;

	for (i = 0; i < res->rows; i++) {
		for (j = 0; j < res->cols; j++) {
			printf("%5d", res->array[i][j]);
		}
		printf("\n");
	}
}


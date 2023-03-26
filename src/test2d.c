#include <config.h>
#include <stdio.h>
#include <string.h>
#include "lib/array/2d.h"

int test2darray(void)
{
	struct array_2d m1;
    struct array_2d m2;
    struct array_2d *res;

	if (fill_2d(&m1)) {
		return 1;
	}

    if (fill_2d(&m2)) {
        return 1;
    }

    res = multiply(&m1, &m2);

    print_2d(&m1);
    print_2d(&m2);

    print_2d(res);

	return 0;
}

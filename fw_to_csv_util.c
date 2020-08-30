#include <stdio.h>
#include <stdlib.h>

#include "fw_to_csv_util.h"

int add(IntArray *i_arr, int value) {
		// Resize the array if need be
		if (i_arr->size == i_arr->capacity) {
				int new_capacity = 2 * i_arr->capacity;
				int *new_arr = realloc(i_arr->arr, new_capacity * sizeof(int));
				if (new_arr == NULL) {
						return 1;
				}

				i_arr->arr = new_arr;
				i_arr->capacity = new_capacity;
		}

		(i_arr->arr)[i_arr->size] = value;
		i_arr->size += 1;

		return 0;
}

void print_len_arr(IntArray *i_arr) {
		for (int i = 0; i < i_arr->size; i++) {
				printf("%d ", (i_arr->arr)[i]);
		}
		printf("\n");
}

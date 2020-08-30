#ifndef FW_TO_CSV_UTIL_H
#define FW_TO_CSV_UTIL_H

typedef struct {
		int *arr;
		int size; // When creating a new IntArray, size should always be 0
		int capacity;
} IntArray;

int add(IntArray*, int);

int get_lens_from_file(IntArray*, char*);

void print_len_arr(IntArray*);

#endif

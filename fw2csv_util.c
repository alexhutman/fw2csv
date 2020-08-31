#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int get_lens_from_file(IntArray *i_arr, char *fname) {
		FILE *fp = fopen(fname, "r");

		if (fp == NULL) {
				fprintf(stderr, "ERROR: file %s does not exist\n", fname);
				return 1;
		}

		char *line = NULL;
		size_t len = 0;
		ssize_t read;

		int cur_len = 0;
		while ((read = getline(&line, &len, fp)) != -1) {
				cur_len = atoi(line);
				i_arr->sum_lengths += cur_len;
				add(i_arr, cur_len);

				if (cur_len > i_arr->max_length) {
						i_arr->max_length = cur_len;
				}
		}

		free(line);
		if (fclose(fp)) {
				fprintf(stderr, "Error closing file %s\n", fname);
				return 1;
		}

		return 0;
}

// Adapted from https://stackoverflow.com/a/26620524/6708303
void slice_str(char *str, char *buffer, size_t start, size_t end) {
    size_t j = 0;
    for (size_t i = start; i <= end; ++i) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

char *rtrim(char s[]) {
		char *end = s + strlen(s) - 1;
		while (isspace(*end)) {
				end--;
		}
		*(end+1) = '\0';
		return s;
}

int parse_fw_file(IntArray *i_arr, char *fw_fname) {
		FILE *fp = fopen(fw_fname, "r");

		if (fp == NULL) {
				fprintf(stderr, "ERROR: file %s does not exist\n", fw_fname);
				return 1;
		}

		char *line = NULL;
		size_t len = 0;
		ssize_t read;

		int cur_line = 1;
		while ((read = getline(&line, &len, fp)) != -1) {
				if ((read-1) != i_arr->sum_lengths) {
						fprintf(stderr, "Error: line %d is of incorrect length. Expected %d, got %zd\n", cur_line, i_arr->sum_lengths, read-1);
						return 1;
				}

				char buffer[i_arr->max_length + 1];
				int cur_index = 0;
				for (int col = 0; col < ((i_arr->size)-1); col++) {
						slice_str(line, buffer, cur_index, cur_index + (i_arr->arr)[col]-1);
						printf("%s,", rtrim(buffer));
						cur_index += (i_arr->arr)[col];
				}

				// Do the last column manually to omit the comma and print new line
				slice_str(line, buffer, cur_index, cur_index + (i_arr->arr)[(i_arr->size)-1]-1);
				printf("%s\n", rtrim(buffer));

				cur_line += 1;
		}

		free(line);
		if (fclose(fp)) {
				fprintf(stderr, "Error closing file %s\n", fw_fname);
				return 1;
		}

		return 0;
}

void print_len_arr(IntArray *i_arr) {
		for (int i = 0; i < i_arr->size; i++) {
				printf("%d ", (i_arr->arr)[i]);
		}
		printf("\n");
}

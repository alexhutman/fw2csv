#include <stdio.h>
#include <stdlib.h>

#include "../fw2csv_util.h"

#define N_COLS 10

int main(int argc, char *argv[]) {
		IntArray test_lengths = {malloc(N_COLS * sizeof(int)), 0, N_COLS, 0, 0};

		printf("Initializing array...\n");
		for (int i = 0; i < test_lengths.capacity; i++) {
				add(&test_lengths, i);
		}

		print_len_arr(&test_lengths);

		printf("Size: %d, capacity: %d, sum: %d, max: %d\n", test_lengths.size, test_lengths.capacity, test_lengths.sum_lengths, test_lengths.max_length);
		printf("Adding values from test file to array...\n");

		// You have to call this test from the base directory of the project for this file to load correctly
		if (get_lens_from_file(&test_lengths, "test/lengths.txt")) {
				return 1;
		}

		printf("Size: %d, capacity: %d, sum: %d, max: %d\n", test_lengths.size, test_lengths.capacity, test_lengths.sum_lengths, test_lengths.max_length);

		print_len_arr(&test_lengths);
		free(test_lengths.arr);

		IntArray fw_lengths = {malloc(N_COLS * sizeof(int)), 0, N_COLS, 0};
		if (get_lens_from_file(&fw_lengths, "test/lengths.txt")) {
				return 1;
		}

		if (parse_fw_file(&fw_lengths, "test/fixed_width.txt")) {
				return 1;
		}

		free(fw_lengths.arr);

		return 0;
}

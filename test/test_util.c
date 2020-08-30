#include <stdio.h>
#include <stdlib.h>

#include "../fw_to_csv_util.h"

#define N_COLS 10

int main(int argc, char *argv[]) {
		IntArray lengths = {malloc(N_COLS * sizeof(int)), 0, N_COLS};

		printf("Initializing array...\n");
		for (int i = 0; i < lengths.capacity; i++) {
				add(&lengths, i);
		}

		print_len_arr(&lengths);

		printf("Size: %d, capacity: %d\n", lengths.size, lengths.capacity);
		printf("Adding more values to array...\n");
		add(&lengths, N_COLS);
		printf("Size: %d, capacity: %d\n", lengths.size, lengths.capacity);
		add(&lengths, N_COLS+1);
		printf("Size: %d, capacity: %d\n", lengths.size, lengths.capacity);

		print_len_arr(&lengths);

		free(lengths.arr);

		return 0;
}

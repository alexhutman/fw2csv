#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include "fw_to_csv_util.h"


#define N_COLS 10

int main(int argc, char *argv[]) {
		if (argc != 2) {
				char *prog_name = basename(argv[0]);
				fprintf(stderr, "Usage: %s <file_to_ingest> <lengths_file>\nWhere <lengths_file> is a file where line `n` is the length of column `n`\n", prog_name);
				return 1;
		}

		char *fname = argv[1];
		IntArray lengths = {malloc(N_COLS * sizeof(int)), 0, N_COLS};

		if (get_lens_from_file(&lengths, fname)) {
				return 1;
		}

		free(lengths.arr);
}

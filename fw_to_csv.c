#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#include "fw_to_csv_util.h"


#define N_COLS 10

int main(int argc, char *argv[]) {
		if (argc != 3) {
				char *prog_name = basename(argv[0]);
				fprintf(stderr, "Usage: %s <file_to_ingest> <lengths_file>\nWhere <lengths_file> is a file where line `n` is the length of column `n`\n", prog_name);
				return 1;
		}

		char *lens_fname = argv[2];
		IntArray lengths = {malloc(N_COLS * sizeof(int)), 0, N_COLS, 0};

		if (get_lens_from_file(&lengths, lens_fname)) {
				return 1;
		}

		char *fw_fname = argv[1];
		parse_fw_file(&lengths, fw_fname);

		free(lengths.arr);
}

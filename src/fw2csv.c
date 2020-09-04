#include <ctype.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fw2csv_util.h"


#define N_COLS 10

void print_usage() {
		fprintf(stderr, "Usage: fw2csv -i <file_to_ingest> -l <lengths_file> [-d '<delimiter>']\n");
}

int main(int argc, char *argv[]) {
		int iflag = 0, lflag = 0, dflag = 0;
		char *fw_fname;
		char *lens_fname;
		char delimiter = ',';

		int option;
		while ((option = getopt(argc, argv, "i:l:d:")) != -1) {
				switch (option) {
						case 'i':
								iflag = 1;
								fw_fname = optarg;
								break;
						case 'l':
								lflag = 1;
								lens_fname = optarg;
								break;
						case 'd':
								if (strlen(optarg) != 1) {
										fprintf(stderr, "Delimiter must be 1 character long\n");
										print_usage();
										return 1;
								} else {
										dflag = 1;
										delimiter = *optarg;
								}
								break;
						case '?':
								return 1;
						default:
								print_usage();
								return 1;
				}
		}

		if (!iflag || !lflag) {
				print_usage();
				return 1;
		}


		IntArray lengths = {malloc(N_COLS * sizeof(int)), 0, N_COLS, 0};

		if (get_lens_from_file(&lengths, lens_fname)) {
				return 1;
		}

		parse_fw_file(&lengths, fw_fname, delimiter);

		free(lengths.arr);
}

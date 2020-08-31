CC       = gcc
CFLAGS   = -O3
EXE_NAME = fw2csv

$(EXE_NAME): fw2csv_util.o fw2csv.o 
	$(CC) $(CFLAGS) fw2csv_util.o fw2csv.o -o $(EXE_NAME)

fw2csv_util.o: src/fw2csv_util.c src/fw2csv_util.h
	$(CC) $(CFLAGS) -c src/fw2csv_util.c

fw2csv.o: src/fw2csv.c src/fw2csv_util.h
	$(CC) $(CFLAGS) -c src/fw2csv.c

clean:
	rm -f *.o $(EXE_NAME)

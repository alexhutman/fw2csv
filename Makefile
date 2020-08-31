fw2csv: fw2csv.o fw2csv_util.o
	gcc fw2csv.o fw2csv_util.o -o fw2csv

fw2csv.o: fw2csv.c
	gcc -c fw2csv.c

fw2csv_util.o: fw2csv_util.c fw2csv_util.h
	gcc -c fw2csv_util.c

clean:
	rm *.o fw2csv

CC = gcc
CFLAGS = -O3 -g -std=c99 -Wall -Wshadow -Wvla -pedantic

a6: a6.c
	$(CC) $(CFLAGS) a6.c -o a6

clean:
	rm -f a6 out_file1 out_file2 out_file3
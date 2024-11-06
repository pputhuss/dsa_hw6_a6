CC = gcc
CFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic

a6: main.c
	$(CC) $(CFLAGS) main.c -o a6

clean:
	rm -f a6 out_file1 out_file2 out_file3
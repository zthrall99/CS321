default: c

all: c

c: FileCopy

FileCopy: FileCopy.c
	gcc-9 FileCopy.c -o FileCopy

clean:
	rm -f FileCopy
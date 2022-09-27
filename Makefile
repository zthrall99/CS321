default: c

all: c

c: FileCopy

FileCopy: FileCopy.c
	gcc FileCopy.c -o FileCopy

clean:
	rm -f FileCopy
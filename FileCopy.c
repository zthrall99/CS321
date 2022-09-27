/*****************************************************************************
 * FileCopy.c                                                                 
 * Name: Zach Thrall
 *****************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	//setting command line arguments
	if (argc != 3) {
			fprintf(stderr, "Usage: %s [absolute URI]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	char *inputFile = argv[1];
	char *outputFile = argv[2];
	
	//variables
	FILE *file1;
	FILE *file2;
	char fileContents[256];
	
	//opening input file and error handling if file doesn't exist
	file1 = fopen(inputFile, "r");
	if(file1 == NULL){
		perror("file1");
		exit(1);
	}

	//using fseek to find the end position of the last character in the text file
	fseek(file1, 0, SEEK_END);

	//using ftell to store an int of the end position found by fseek
	int pos = ftell(file1);

	//using fseek to reset the position of the cursor back to the beginning 
	//of the text file
	fseek(file1, 0, SEEK_SET);		
	
	//reading the contents of the file into the buffer and closing the file
	fread(fileContents, pos, 1, file1);
	fclose(file1);
	
	//opening output file, writing contents from buffer, closing said file, and error handling
	file2 = fopen(outputFile, "r+");
	if(file2 == NULL){
		perror("file2");
		exit(1);
	}
	fwrite(fileContents, pos, 1, file2);
	fclose(file2);
}
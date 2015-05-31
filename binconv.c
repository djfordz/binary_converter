#include <stdio.h>
#include <stdlib.h>

// Prototypes
int fromBinary(char *string);

int main(int argc, char **argv) {

	// check for proper number of arguments.
	if(argc != 2) {
		perror("usage: ./binconv <file>");
	}

	//store file.
	char *file = argv[1];

	//open file.
	FILE *inptr = fopen(file, "r");
	if(inptr == NULL) {
		perror("Unable to open file.");
		return -1;
	}

	//create or open write file for removal of spaces.
	FILE *outptr = fopen("convtext.txt", "wb");
	if(outptr == NULL) {
		perror("Unable to create file");
		fclose(inptr);
		return -1;
	}

	//declare variables.
	char chkspc;
	int count = 0;
	
	//read each char from file, ignoring spaces write to new file and count chars.
	while((chkspc = fgetc(inptr)) != EOF) {
		if(chkspc == ' ') {
			;
		} else {
			putc(chkspc, outptr);
			count++;
		}
	}

	// close files.
	fclose(outptr);
	fclose(inptr);

	//open newly created file to read.
	FILE *readptr = fopen("convtext.txt", "rb");
	if(readptr == NULL) {
		perror("could not open file for read.");
		return -1;
	}

	// create buffer and text variables on heap.
	char *buf = (char *)malloc(sizeof(char) * 9);
	char *txt = (char *)malloc(sizeof(char) * count);
	if(txt == NULL || buf == NULL) {
		perror("could not allocate memory");
		return -1;
	}
	
	// read string of new file.
	while(fgets(buf, 9, readptr) != NULL) {

		// declare pointer to buffer.
		char *txtconv;

		//store buffer.
		txtconv = buf;

		//end string.
		txtconv[9] = '\0';

		//declare variable.
		int i = 0;

		//convert to text.
		txt[i] = fromBinary(txtconv);

		//count.
		i += 8;

		//print string.
		printf("%s", txt);

	}

	//print new line.
	printf("\n");

	// clean up.
	free(txt);
	free(buf);
	fclose(readptr);

	//that's all folks.
	return 0;
}

int fromBinary(char *string) {
	return (int) strtol(string, NULL, 2);
}

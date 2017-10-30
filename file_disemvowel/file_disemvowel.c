#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 1024
/* 
 * Returns true if c is a vowel (upper or lower case), and 
 * false otherwise. 
 */ 
bool is_vowel(char c) { 
    const char* vowels = "AaEeIiOoUu";
    if (strchr(vowels, c) != '\0') {
    	return true;
    }
    return false;
}

/*
 * Copy all the non-vowels from in_buf to out_buf. 
 * num_chars indicates how many characters are in in_buf, 
 * and this function should return the number of non-vowels that
 * that were copied over.
 */
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
     int i, j, non_vowels;
     
     non_vowels = 0;
     j = 0;
     for (i=0; i<num_chars; ++i) {
    	if (!is_vowel(in_buf[i])) {
	    out_buf[j] = in_buf[i];
	    ++j;
	    ++non_vowels;
	} 
     }
     return non_vowels;
}

/*
 * Copy all the non-vowels from inputFile to outputFile.
 * Create input and output buffers, and use fread() to repeatedly read
 * in a buffer of data, copy the non-vowels to the output buffer, and
 * use fwrite to write that out. 
 */
void disemvowel(FILE* inputFile, FILE* outputFile) { 
    char* in_buf = malloc(BUF_SIZE*sizeof(char)); 
    char* out_buf = malloc(BUF_SIZE*sizeof(char));
    int current_buf_size, copied_vowels;
    
    while ((current_buf_size = fread(in_buf, sizeof(char), BUF_SIZE, inputFile))) {
        copied_vowels = copy_non_vowels(current_buf_size, in_buf, out_buf);
        fwrite(out_buf, sizeof(char), copied_vowels, outputFile);
    }
    
   

    free(in_buf);
    free(out_buf);    
}

int main(int argc, char *argv[]) { 
    FILE *inputFile; 
    FILE *outputFile;

    // Code that processes the command line arguments 
    // and sets up inputFile and outputFile.
    switch(argc) {
    	case 1:		// No parameters, use stdin and stdout.
	  inputFile = stdin;
	  outputFile = stdout;
	  break;

	case 2:		// Input file only, use input file and stdout.
	  if ((inputFile = fopen(argv[1], "r")) == NULL) {
	      puts("Input file cannot be opened.");
	      exit(0);
	  }
	  outputFile = stdout;
	  break;

	case 3: 	// Both files present, use input file and output file.
	  if ((inputFile = fopen(argv[1], "r")) == NULL) {
	      puts("Input file cannot be opened.");
	      exit(0);
	  }
	  if ((outputFile = fopen(argv[2], "r+")) == NULL) {
	      puts("Output file cannot be opened.");
	      exit(0);
	  }
	  break;

	default:	// Too many parameters, error.
	  puts("Too many arguments.");
	  exit(0);
    }
   
    disemvowel(inputFile, outputFile);
    
    fclose(inputFile);
    fclose(outputFile);

    return 0; 
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>

#define MAX_FTW_DEPTH 16

static int num_dirs, num_regular;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_F) {
    	++num_regular;
	return 0;
    }
    else if (typeflag == FTW_D) {
    	++num_dirs;
	return 0;
    }
    else {
    	printf("Error during callback function.\n");
	return 1;
    } 
}

int main(int argc, char* argv[]) {
    // Check arguments
    if (argc != 2) {
    	printf("Usage: %s <path>.\n", argv[0]);
	printf("	where <path> is the name of the file or root of the tree you want to summarize.\n");
    }   
    
    // Setup counters
    num_dirs = 0;
    num_regular = 0;
    int errcode;
    // Begin traversal, updating counters
    if ((errcode = ftw(argv[1], callback, MAX_FTW_DEPTH)) != 0) {
        printf("There was an error during the ftw() traversal.\n");
	return 1;	
    }

    // Print out results
    printf("There were %d directories.\n", num_dirs);
    printf("There were %d regular files.\n", num_regular);

    return 0;
    
}

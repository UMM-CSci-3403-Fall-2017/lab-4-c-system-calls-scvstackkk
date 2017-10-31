#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

/*
 * Use the stat() function (try "man 2 stat") to determine if the file
 * referenced by path is a directory or not.  Call stat, and then use
 * S_ISDIR to see if the file is a directory. Make sure you check the
 * return value from stat in case there is a problem, e.g., maybe the
 * the file doesn't actually exist.
 */
bool is_dir(const char* path) {
    struct stat buf;
    bool is_dir;
    int errcode;
    
    if ((errcode = stat(path, &buf)) != 0) {
       printf("stat() returned with error code %d.\n", errcode);
       return 1;
    }
    else {
      is_dir = S_ISDIR(buf.st_mode);
      return is_dir;
    }
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

/*
 * Update the number of directories seen, use opendir() to open the
 * directory, and then use readdir() to loop through the entries
 * and process them. You have to be careful not to process the
 * "." and ".." directory entries, or you'll end up spinning in
 * (infinite) loops. Also make sure you closedir() when you're done.
 *
 * You'll also want to use chdir() to move into this new directory,
 * with a matching call to chdir() to move back out of it when you're
 * done.
 */
void process_directory(const char* path) {
    DIR* current_dir;
    struct dirent* ds;
    int errcode;
    
    // Opens the target directory. Throws an error if the pointer returned is "NULL".
    if ((current_dir = opendir(path)) == NULL) {
	    printf("opendir() returned a null pointer while opening %s.\n", path);
	    return;
    } 
    else {
	// Move to the target directory. Throws an error if there are issues.
        if ((errcode = chdir(path)) != 0) {
            printf("chdir() returned with error code %d while moving to %s.\n", errcode, path);
   	    return;
        }   	    	    
	// Loop through the contents of the current directory, avoiding "." and "..".
    	while ((ds = readdir(current_dir)) != NULL) {
    	   if (strcmp(ds->d_name, ".") != 0 && strcmp(ds->d_name, "..") != 0) {
    	       process_path(ds->d_name);
	   } 
	}
	// Close the current directory or throw an error if there are issues. 
	if ((errcode = closedir(current_dir)) != 0) {
	    printf("closedir() returned with error code %d.\n", errcode);
	    return;
	}
	// Move out of the current directory. Throwns an error if there are issues.
	if ((errcode = chdir("..")) != 0) {
	    printf("chdir() returned with error code %d while moving out of %s.\n", errcode, path);
	    return;
	}
        // Increment the number of directories.
	++num_dirs;
    }    
}

/*
 * Update the number of regular files.
 */
void process_file(const char* path) {
    ++num_regular; 
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}

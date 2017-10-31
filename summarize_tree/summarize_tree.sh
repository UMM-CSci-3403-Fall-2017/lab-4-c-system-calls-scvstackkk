#!/usr/bin/bash

# Get the directory to be summarized.
TARGET_DIR=$1

# Count the number of newline directories or regular files.
NUM_DIRS=$(find "$TARGET_DIR"/ -type d | wc -l)
NUM_REGULAR=$(find "$TARGET_DIR"/ -type f | wc -l)

# Print out the result.
echo "There were $NUM_DIRS directories."
echo "There were $NUM_REGULAR regular files."



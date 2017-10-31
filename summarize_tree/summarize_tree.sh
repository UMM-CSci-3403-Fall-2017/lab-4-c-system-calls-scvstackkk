#!/usr/bin/bash

TARGET_DIR=$1

NUM_DIRS=$(find "$TARGET_DIR"/ -type d | wc -l)
NUM_REGULAR=$(find "$TARGET_DIR"/ -type f | wc -l)

echo "There were $NUM_DIRS directories."
echo "There were $NUM_REGULAR regular files."



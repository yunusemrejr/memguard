#!/bin/bash

# Compile the program
echo "Compiling test.c and memguard.c..."
gcc -o test test.c memguard.c -Wall -Wextra

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    echo "Running the test program..."
    echo "------------------------"
    ./test
    echo "------------------------"
    echo "Test completed."
else
    echo "Compilation failed. Please check your code for errors."
fi

# Clean up
echo "Cleaning up..."
rm -f test

## Coding Practice for data structures and algorithms

This repository consists of simple implementations of data structures and algorithms which would be
useful for Software Certifications where importing a library is prohibited.

To practice, delete the source code and implement it from scratch. If implemented correctly, it
should pass the unit tests.


### How to test
1. Create a `build` folder to contain the binary and CMake generated files and move into that
   directory.
1. Enter command `cmake <path to directory of CMakeList.txt>` to generate CMake files.
1. Enter command `make` to build the binary from the generated Makefile
1. Run the binary to check if all test cases pass
1. Some test cases (e.g. BFS) expects input from stdin, for that case simply
   `cat <test_inputs file>` and pipe it onto the binary (e.g. `cat ../test_input.txt | ./test_bfs`)

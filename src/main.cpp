#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <util.h>

using std::string;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: brainfrick <input file>\n");
        exit(1);
    }

    string input_filepath = string(argv[1]);

    if (!validate_file(input_filepath)) {
        fprintf(stderr, "Error parsing file %s. Exiting.\n", input_filepath.c_str());
        exit(1);
    }
}
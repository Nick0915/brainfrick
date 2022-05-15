#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "util.h"

#include "Interpreter.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: brainfrick <input file>\n");
        exit(1);
    }

    std::string input_filepath(argv[1]);

    // check extension and existence
    if (!validate_file(input_filepath))
        exit(1);

    // read file
    std::string content = read_file(input_filepath);

    // syntax checking
    // literally just checking if bracket pairs match lol
    if (!check_bracket_pairs(content))
        exit(1);

    Interpreter interpreter(content);

    while (true) {
        if (!interpreter.execute()) {
            break;
        }
    }
}
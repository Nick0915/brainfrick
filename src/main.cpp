#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "util.h"

#include "Interpreter.h"

int main(
#ifndef DEFAULT_FILE
    int argc, char *argv[]
#endif
) {
#ifdef DEFAULT_FILE
    std::string input_filepath("res/hello_world.bf");
#else
    if (argc != 2) {
        fprintf(stderr, "Usage: brainfrick <input file>\n");
        exit(1);
    }

    std::string input_filepath(argv[1]);
#endif

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

    while (interpreter.has_next()) {
        interpreter.execute();
    }

    return 0;
}
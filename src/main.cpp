#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <util.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: brainfrick <input file>\n");
        exit(1);
    }

    std::string input_filepath(argv[1]);

    if (!validate_file(input_filepath))
        exit(1);

    std::string content = read_file(input_filepath);

    if (!check_bracket_pairs(content)) {
        exit(1);
    }
}
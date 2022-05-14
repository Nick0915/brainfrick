#include <stdio.h>

#include <sstream>

#include "util.h"

/**
 * Converst a string to exclusively lower case. Any non-letter characters aren't
 * changed.
 *
 * @param input the string to convert.
 * @return a string with no capital letters.
 */
static std::string to_lower_case(const std::string& input) {
    std::stringstream stream;
    for (size_t i = 0; i < input.size(); i++) {
        char curr = input[i];
        // if it is a capital letter
        if (curr >= 'A' && curr <= 'Z') {
            stream << (char) (curr + ('a' - 'A'));
        } else {
            stream << curr;
        }
    }
    return stream.str();
}

/**
 * Checks the extension of the given file to see if it matches the '.bf'
 * extension required.
 *
 * @param filepath the relative path to the file.
 * @return true if the file extension is valid, false otherwise.
 */
static bool check_file_extension(const std::string& filepath) {
    // test the extension name
    uint name_size = filepath.size();
    uint dot_index = filepath.find('.');
    if (dot_index == std::string::npos || dot_index > filepath.size()) {
        fprintf(stderr, "File must have the .bf extension.\n");
        return false;
    }
    std::string extension = to_lower_case(filepath.substr(dot_index, name_size));
    if (extension.compare(".bf") == 0 || extension.compare(".b") == 0) {
        return true;
    }
    fprintf(
        stderr,
        "Cannot accept files with '%s' extension. Extension must be '.bf'.\n",
        extension.c_str()
    );
    return false;
}

/**
 * Makes sure the given file exists.
 *
 * @param filepath the relative path to the file.
 * @return true if the file exists, false otherwise.
 */
static bool check_file_exists(const std::string& filepath) {
    FILE* f = fopen(filepath.c_str(), "r");
    if (f) {
        fclose(f);
        return true;
    }
    fprintf(stderr, "File %s does not exist.\n", filepath.c_str());
    return false;
}

/**
 * Makes sure the brackets in the source code match up. For example, [[]] is a
 * valid set of brackets, but [[] is not.
 *
 * @param filepath the relative path to the file containing the source.
 * @return true if the brackets are valid, false otherwise.
 */
bool check_bracket_pairs(const std::string& filepath) {
    return false;
}

/**
 * Returns whether a file is a valid brainf*ck file or not. Performs a number of
 * checks and returns false if any of them fail:
 * 1. The file name must end in .bf (or .BF, or any other capitalization of .bf)
 * 2. The file must exist
 *
 * @param filepath the relative path to the file.
 */
bool validate_file(const std::string& filepath) {
    return check_file_extension(filepath) &&
           check_file_exists(filepath) /* &&
           check_bracket_pairs(filepath) */;
}
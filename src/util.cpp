#include <stdio.h>

#include <fstream>
#include <sstream>
#include <stack>
#include <tuple>

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
    uint dot_index = filepath.find_last_of('.');
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
        "Cannot accept files with '%s' extension. Extension must be '.bf' or '.b'.\n",
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
 * Returns whether a file is a valid brainf*ck file or not. Performs a number of
 * checks and returns false if any of them fail:
 * 1. The file name must end in .bf (or .BF, or any other capitalization of .bf)
 * 2. The file must exist
 *
 * @param filepath the relative path to the file.
 */
bool validate_file(const std::string& filepath) {
    if (!check_file_extension(filepath))
        return false;
    if (!check_file_exists(filepath))
        return false;

    return true;
}

/**
 * Reads the content of the given file into a string.
 *
 * @param filepath the relative path to the file.
 * @return a string containing the contents of the file.
 */
std::string read_file(const std::string& filepath) {
    // https://stackoverflow.com/questions/2912520/read-file-contents-into-a-string-in-c
    std::ifstream stream(filepath);
    std::string content;
    content.assign(
        std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>()
    );
    return content;
}

/**
 * Makes sure the brackets in the source code match up. For example, [[]] is a
 * valid set of brackets, but [[] is not.
 *
 * @param content the source to analyze.
 * @return true if the brackets are valid, false otherwise.
 */
bool check_bracket_pairs(const std::string& content) {
    ssize_t stack_size = 0;

    size_t current_line = 1;
    size_t current_column = 1;

    // [ (line, col), (line, col), ...]
    std::stack<std::tuple<uint, uint>> unmatched_left_braces;

    for (size_t i = 0; i < content.size(); i++) {
        if (content[i] == '\n') {
            // increment line counter
            current_line++;
            // reset column counter
            current_column = 1;
        }
        if (content[i] == '[') {
            unmatched_left_braces.push(
                std::tuple<uint, uint>(
                    current_line, current_column
                )
            );
            stack_size++;
        }
        if (content[i] == ']') {
            unmatched_left_braces.pop();
            stack_size--;
        }
        // means there were less '[' than ']'
        if (stack_size < 0) {
            fprintf(
                stderr,
                "Missing matching left bracket for a right bracket at %lu:%lu.\n",
                current_line, current_column - 1
            );
            return false;
        }
        current_column++;
    }
    // means there were more '[' than ']'
    if (stack_size != 0) {
        std::tuple<uint, uint> unmatched_brace_pos = unmatched_left_braces.top();
        fprintf(
            stderr,
            "Missing matching right bracket for a left bracket at %u:%u.\n",
            std::get<0>(unmatched_brace_pos), std::get<1>(unmatched_brace_pos) - 1
        );
        return false;
    }
    return true;
}

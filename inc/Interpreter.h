#pragma once

#include <limits.h>

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

#define TAPE_SIZE USHRT_MAX

class Interpreter {
public:
    Interpreter(std::string& source);

    bool execute();

    bool has_next();

    // debugging methods
    size_t get_prog_counter();
    char get_source_char_at(size_t index);
    char get_next_source_char();
    ushort get_address_pointer();
    ushort get_max_used_address();
    uint8_t get_tape_at(ushort index);
private:
    std::string& m_source; // source code in text

    size_t m_prog_counter; // location in source

    ushort m_address_pointer; // location of head
    ushort m_max_used_address; // if wrapping ever reaches this, error and abort

    uint8_t m_tape[TAPE_SIZE];
    size_t m_times_looped;

    static bool is_valid_token(char token);
    int find_matching_right_bracket();
    int find_matching_left_bracket();
    std::tuple<size_t, size_t> get_line_and_col(size_t index);

    // brainf*ck instructions as functions
    void move_right();
    void move_left();
    void increment();
    void decrement();
    void write();
    void read();
    void jump_if_zero();
    void jump_unless_zero();
};

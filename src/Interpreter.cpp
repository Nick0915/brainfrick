#include "Interpreter.h"

#include <stdlib.h>

bool Interpreter::is_valid_token(char token) {
    switch (token) {
        case '>': case '<':
        case '+': case '-':
        case ',': case '.':
        case '[': case ']':
            return true;
        default:
            return false;
    }
}

int Interpreter::find_matching_right_bracket() {
    int stack_size = 0;
    for (size_t i = m_prog_counter + 1; i < m_source.size(); i++) {
        if (m_source[i] == '[') {
            stack_size++;
        } else if (m_source[i] == ']') {
            stack_size--;
        }
        if (stack_size < 0) {
            return i;
        }
    }
    fprintf(
        stderr,
        "Something went wrong with the interpreter. Matching right bracket not found. Exiting.\n"
    );
    exit(1);
}

int Interpreter::find_matching_left_bracket() {
    int stack_size = 0;
    for (ssize_t i = (ssize_t) m_prog_counter - 1; i >= 0; i--) {
        if (m_source[i] == ']') {
            stack_size++;
        } else if (m_source[i] == '[') {
            stack_size--;
        }
        if (stack_size < 0) {
            return i;
        }
    }
    fprintf(
        stderr,
        "Something went wrong with the interpreter. Matching left bracket not found. Exiting.\n"
    );
    exit(1);
}

Interpreter::Interpreter(std::string& source)
: m_source(source), m_prog_counter(0), m_address_pointer(0),
m_max_used_address(0), m_times_looped(0) {
    for (ushort i = 0; i < TAPE_SIZE; i++) {
        m_tape[i] = 0;
    }
}

bool Interpreter::execute() {
    char curr = m_source[m_prog_counter];
    while (!is_valid_token(curr)) {
        m_prog_counter++;
        // ran out of instructions
        if (m_prog_counter >= m_source.size())
            return false;
    }

    auto tup = get_line_and_col(m_prog_counter);
    printf(
        "Processing command: '%c' at %lu:%lu\n",
        curr, std::get<0>(tup), std::get<1>(tup)
    );

    switch (curr) {
        case '>': move_right(); break;
        case '<': move_left(); break;
        case '+': increment(); break;
        case '-': decrement(); break;
        case '.': write(); break;
        case ',': read(); break;
        case '[': jump_if_zero(); break;
        case ']': jump_unless_zero(); break;
        default:
            fprintf(
                stderr,
                "Something went wrong with the interpreter, invalid character %c recognized as valid token. Exiting.\n",
                curr
            );
            exit(1);
    }

    return true;
}

void Interpreter::move_right() {
    ushort old = m_address_pointer;
    m_address_pointer++;

    // check for overflow
    if (m_address_pointer < old) {
        auto tup = get_line_and_col(m_prog_counter);
        fprintf(
            stderr,
            "Ran out of memory during move_right at %lu:%lu. Looped a total of %lu times. Exiting.\n",
            std::get<0>(tup), std::get<1>(tup), m_times_looped
        );
        exit(1);
    }

    // set the new max
    if (m_address_pointer > m_max_used_address) {
        m_max_used_address = m_address_pointer;
    }

    // move to next instruction
    //* NOTE: if the next instruction happens to be an invalid token, the
    //* method will keep looping until it finds the next valid token, so we
    //* don't need to do it here.
    m_prog_counter++;
}

void Interpreter::move_left() {
    ushort old = m_address_pointer;
    m_address_pointer--;

    // if overflowed and encroaching on m_max_used_address
    if (m_address_pointer > old) {
        if (m_address_pointer <= m_max_used_address) {
            auto tup = get_line_and_col(m_prog_counter);
            fprintf(
                stderr,
                "Ran out of memory during left at %lu:%lu. Looped a total of %lu times. Exiting.\n",
                std::get<0>(tup), std::get<1>(tup), m_times_looped
            );
            exit(1);
        }
    }

    // move to next instruction
    m_prog_counter++;
}

void Interpreter::increment() {
    m_tape[m_address_pointer]++;
    m_prog_counter++;
}

void Interpreter::decrement() {
    m_tape[m_address_pointer]--;
    m_prog_counter++;
}

void Interpreter::write() {
    // putc((char) m_tape[m_address_pointer], stdout);
    printf("%c", m_tape[m_address_pointer]);
    m_prog_counter++;
}

void Interpreter::read() {
    int in = getc(stdin);
    if (in == EOF) {
        m_tape[m_address_pointer] = 0;
    } else {
        m_tape[m_address_pointer] = (char) in;
    }
    m_prog_counter++;
}

void Interpreter::jump_if_zero() {
    if (m_tape[m_address_pointer] == 0)
        m_prog_counter = find_matching_right_bracket();
    else
        m_prog_counter++;
}

void Interpreter::jump_unless_zero() {
    if (m_tape[m_address_pointer] != 0) {
        m_prog_counter = find_matching_left_bracket();
        m_times_looped++;
    } else
        m_prog_counter++;
}

size_t Interpreter::get_prog_counter() {
    return m_prog_counter;
}

char Interpreter::get_source_char_at(size_t index) {
    return m_source[index];
}

ushort Interpreter::get_address_pointer() {
    return m_address_pointer;
}

ushort Interpreter::get_max_used_address() {
    return m_max_used_address;
}

uint8_t Interpreter::get_tape_at(ushort index) {
    return m_tape[index];
}

std::tuple<size_t, size_t> Interpreter::get_line_and_col(size_t index) {
    int line = 1;
    int col = 1;
    for (size_t i = 0; i < index; i++) {
        if (m_source[i] == '\n') {
            line++;
            col = 1;
        } else {
            col++;
        }
    }
    return std::tuple<size_t, size_t>(line, col);
}

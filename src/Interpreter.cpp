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

Interpreter::Interpreter(std::string& source)
: m_source(source), m_prog_counter(0), m_address_pointer(0),
m_max_used_address(0) {
    for (short i = 0; i < TAPE_SIZE; i++) {
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

void Interpreter::move_right() {}
void Interpreter::move_left() {}
void Interpreter::increment() {}
void Interpreter::decrement() {}
void Interpreter::write() {}
void Interpreter::read() {}
void Interpreter::jump_if_zero() {}
void Interpreter::jump_unless_zero() {}

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

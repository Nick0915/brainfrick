# Brainfrick

This is my version of a Brainf*ck interpreter.

## Project status:
UNFINISHED

## Building
The source files are in `src/` and `inc/`.
Object files will be placed in `obj/` and the executable will be placed in `out/`

### Requirements
* Make

### Build Instructions
Run `make` in the project root directory.

## Running
Make sure you are `cd`'d into the same directory as the executable (`out/`).
Run the executable using `./brainfrick`.

### Usage:
`brainfrick <input file>`
where the input file is a `.bf` (given in relative path format) containing brainf*ck source code.

## Credits/Acknowledgements
* [Brainf*ck, Wikipedia](https://en.wikipedia.org/wiki/Brainfuck)
    * Look here to learn more about Brainf*ck and esoteric programming languages.
* [Brainf*ck Specification](https://github.com/brain-lang/brainfuck/blob/master/brainfuck.md).
    * Specification I followed when developing the interpreter.
* Tests:
    * [beer.b](https://github.com/rdebath/Brainfuck/blob/master/testing/Beer.b)
    * [hello_2.b](https://github.com/rdebath/Brainfuck/blob/master/testing/Hello2.b)
    * [hello_world.bf](https://esolangs.org/wiki/Brainfuck)
    * [test.bf](res/beer.b) (made it myself)

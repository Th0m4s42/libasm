# LIBASM

A custom implementation of standard C library functions written in x86_64 Assembly (NASM syntax).

## Description

This project is part of the 42 curriculum. The goal is to understand low-level programming by rewriting basic C standard library functions in Assembly.
It focuses on x86_64 architecture, NASM syntax, and the System V AMD64 ABI calling convention (how arguments are passed via registers like `rdi`, `rsi`, `rdx`, etc.).

## Prerequisite

To compile and use this library, you will need:

- **NASM** (The Netwide Assembler)
- **CC** (standard C compiler, usually Clang or GCC on macOS/Linux)
- **Make**
- **ar** (to create the static library archive)

## Compilation

The project is divided into a mandatory part (`libasm.a`) and a bonus part (`libasm_bonus.a`).

To build both libraries, simply run:

```
make all
```

(Alternatively, you can run *`make mandatory`* or *`make bonus`* to build them separately).

This will compile all `.s` files into `.o` files using NASM (`nasm -f elf64`) and create the static libraries using `ar rcs`.

### Other useful Make rules:

- `make test`: Compiles `test/main.c`, links it with `libasm.a`, and runs the executable to test the mandatory functions.
- `make test_b`: Compiles `test/bonus.c`, links it with both libraries, and runs the executable to test the bonus functions.
- `make clean`: Deletes `the objs` and `objs_bonus` directories.
- `make fclean`: Runs `clean` and deletes the `libasm.a`, `libasm_bonus.a`, and the test binaries.
- `make re`: Runs `fclean` followed by `all` (full rebuild).

## Usage

If you want to write your own `main.c` to test the functions manually, you need to compile it and link it with `libasm.a`.

Example main.c:
```
#include <unistd.h>
#include "libasm.h"

int main(void) {
    char buf[100];
    ft_strcpy(buf, "Hello Assembly!");
    ft_write(1, buf, ft_strlen(buf)); // Write to stdout
    return 0;
}
```
How to compile and run your custom test:
```
# Compile main.c and link it with libasm.a
cc -Wall -Wextra -Werror -Iincs main.c libasm.a -o my_test

# Run the executable
./my_test
```

## Implemented Functions

### Mandatory (`libasm.a`)

| Function | Description | System Call Used |
| :--- | :--- | :--- |
| `ft_strlen` | Calculates the length of a string. | None (pure logic) |
| `ft_strcpy` | Copies a string from source to destination. | None (pure logic) |
| `ft_strcmp` | Compares two strings lexicographically. | None (pure logic) |
| `ft_write` | Writes to a file descriptor. | `syscall write` |
| `ft_read` | Reads from a file descriptor. | `syscall read` |
| `ft_strdup` | Duplicates a string (allocates memory with `malloc`). | `malloc` & pure logic |

### Bonus (`libasm_bonus.a`)

| Function | Description |
| :--- | :--- |
| `ft_atoi_base` | Converts a string to an integer using a specific base. |
| `ft_list_push_front` | Adds a new element at the beginning of a linked list. |

## Technical Details

- **Architecture**: x86_64
- **Syntax**: NASM (Intel syntax)
- **Calling Convention**: System V AMD64 ABI (Linux/macOS)

	- Arguments are passed in: `rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`
	- Return value is stored in: `rax`

- **System Calls**: Functions like `ft_read` and `ft_write` use the `syscall` instruction. The `syscall` number is placed in rax (e.g., `1` for write, `0` for read).
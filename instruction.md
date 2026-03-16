# Instructions for Running Tests and the Assembler

This project uses `make` to compile the source code. The `Makefile` defines several targets for building individual test files and the main assembler program.

## Building and Running Tests

There are several test files provided in the `tests/` directory. You can compile and run each one individually.

### 1. Registers Test
To compile the registers test:
```bash
make test_registers
```
To run it:
```bash
./test_registers.exe
```

### 2. Parser Test
To compile the parser test:
```bash
make test_parser
```
To run it:
```bash
./test_parser.exe
```

### 3. Instruction Table Test
To compile the instruction table test:
```bash
make test_instr_table
```
To run it:
```bash
./test_instr_table.exe
```

### 4. Symbols Test
To compile the symbols test:
```bash
make test_symbols
```
To run it:
```bash
./test_symbols.exe
```

### 5. Encode Test
To compile the encode test:
```bash
make test_encode
```
To run it:
```bash
./test_encode.exe
```

### 6. Assembler Test
To compile the assembler test:
```bash
make test_assembler
```
To run it:
```bash
./test_assembler.exe
```

## Building and Running the Main Assembler

To compile the main assembler program:
```bash
make assembler
```

This will generate an executable named `assembler.exe`. You can run it, typically passing the input assembly file an output file name as arguments (e.g., if supported by `main.c`).

Example usage:
```bash
./assembler.exe
```

## Cleaning up

To remove all the compiled executable files, you can run the `clean` target:
```bash
make clean
```

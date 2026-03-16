# RISC-V Assembler

This project is a two-pass assembler for a subset of the RV32I instruction set, written in C. It translates RISC-V assembly code into 32-bit machine code.

## Supported Instructions

The assembler supports the following instructions:
- **Arithmetic (R-type):** `add`, `sub`, `and`, `or`, `xor`, `sll`, `srl`, `sra`, `slt`, `sltu`
- **Immediate Arithmetic (I-type):** `addi`, `andi`, `ori`, `xori`, `slli`, `srli`, `srai`, `slti`, `sltiu`
- **Memory:** `lb`, `lbu`, `lh`, `lhu`, `lw`, `sb`, `sh`, `sw`
- **Control:** `beq`, `bne`, `blt`, `bge`, `bltu`, `bgeu`, `jal`, `jalr`

## Project Structure

The project is modularly designed with the following components:
- `main`: Program entry point, handling command-line arguments and basic errors.
- `assembler`: Coordinates the two-pass assembly pipeline (building the symbol table in pass 1 and encoding instructions in pass 2).
- `parser`: Extracts labels, mnemonics, and operands from lines of assembly text.
- `registers`: Converts register names (e.g., `x5`, `x31`) to their numeric representation.
- `instr_table`: Stores instruction metadata (format, opcode, funct3, etc.) for lookup.
- `symbols`: Manages the symbol table for branch and label resolution.
- `encode`: Packs instruction fields properly into the final 32-bit machine code format.

## Building and Running

This project uses `make` to compile the source code. The `Makefile` defines several targets for building individual test files and the main assembler program.

### Building the Assembler

To compile the main assembler program:

```bash
make assembler
```

This will generate an executable named `assembler.exe` (or `assembler` depending on your platform).

Example usage:

```bash
./assembler.exe examples/test_case_1.s
```

### Building and Running Tests

There are several test files provided in the `tests/` directory to ensure each module functions correctly. You can compile and run each one individually:

- **Registers Test:**
  ```bash
  make test_registers
  ./test_registers.exe
  ```
- **Parser Test:**
  ```bash
  make test_parser
  ./test_parser.exe
  ```
- **Instruction Table Test:**
  ```bash
  make test_instr_table
  ./test_instr_table.exe
  ```
- **Symbols Test:**
  ```bash
  make test_symbols
  ./test_symbols.exe
  ```
- **Encode Test:**
  ```bash
  make test_encode
  ./test_encode.exe
  ```
- **Assembler Test:**
  ```bash
  make test_assembler
  ./test_assembler.exe
  ```

### Cleaning Up

To remove all the compiled executable files, you can run the `clean` target:

```bash
make clean
```

## Test Report

The compilation and execution of all test suites produce the following successful output:

```text
Running test_parse_register...
All test_parse_register tests passed!
Running test_parse_line...
All test_parse_line tests passed!
Running test_lookup_instruction...
All test_lookup_instruction tests passed!
Running test_symbols...
All test_symbols tests passed!
Running test_encode...
All test_encode tests passed!
Running test_assembler...
All test_assembler tests passed!
```

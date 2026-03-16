CC=gcc
CFLAGS=-Wall -Wextra -Isrc

test_registers: tests/test_registers.c src/registers.c
	$(CC) $(CFLAGS) $^ -o $@

test_parser: tests/test_parser.c src/parser.c src/registers.c
	$(CC) $(CFLAGS) $^ -o $@

test_instr_table: tests/test_instr_table.c src/instr_table.c
	$(CC) $(CFLAGS) $^ -o $@

test_symbols: tests/test_symbols.c src/symbols.c
	$(CC) $(CFLAGS) $^ -o $@

test_encode: tests/test_encode.c src/encode.c src/instr_table.c src/registers.c
	$(CC) $(CFLAGS) $^ -o $@

assembler: src/main.c src/assembler.c src/parser.c src/registers.c src/instr_table.c src/symbols.c src/encode.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f test_registers test_parser test_instr_table test_symbols test_encode test_assembler assembler

test_assembler: tests/test_assembler.c src/assembler.c src/parser.c src/registers.c src/instr_table.c src/symbols.c src/encode.c
	$(CC) $(CFLAGS) $^ -o $@

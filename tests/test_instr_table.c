#include <stdio.h>
#include <assert.h>
#include "instr_table.h"

void test_lookup_instruction() {
    printf("Running test_lookup_instruction...\n");

    const InstrSpec *spec;

    spec = lookup_instruction("add");
    assert(spec != NULL);
    assert(spec->format == FMT_R);
    assert(spec->opcode == 0x33);
    assert(spec->funct3 == 0x0);
    assert(spec->funct7 == 0x00);

    spec = lookup_instruction("addi");
    assert(spec != NULL);
    assert(spec->format == FMT_I);
    assert(spec->opcode == 0x13);
    assert(spec->funct3 == 0x0);

    spec = lookup_instruction("beq");
    assert(spec != NULL);
    assert(spec->format == FMT_B);
    assert(spec->opcode == 0x63);
    assert(spec->funct3 == 0x0);

    spec = lookup_instruction("invalid_instr");
    assert(spec == NULL);

    printf("All test_lookup_instruction tests passed!\n");
}

int main() {
    test_lookup_instruction();
    return 0;
}

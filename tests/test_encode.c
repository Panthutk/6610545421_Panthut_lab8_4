#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "encode.h"
#include "instr_table.h"

void test_encode() {
    printf("Running test_encode...\n");

    const InstrSpec *spec;
    uint32_t inst;

    // Test add x3, x1, x2 (R-type)
    // 0000000 00010 00001 000 00011 0110011
    spec = lookup_instruction("add");
    inst = encode_r(spec->opcode, spec->funct3, spec->funct7, 3, 1, 2);
    assert(inst == 0x002081B3);

    // Test addi x1, x0, 5 (I-type)
    // 000000000101 00000 000 00001 0010011
    spec = lookup_instruction("addi");
    inst = encode_i(spec->opcode, spec->funct3, 1, 0, 5);
    assert(inst == 0x00500093);

    // Test sb x2, 16(x1) (S-type)
    // 0000000 00010 00001 000 10000 0100011
    // imm = 16 = 0x10. imm[11:5] = 0, imm[4:0] = 0x10
    spec = lookup_instruction("sb");
    inst = encode_s(spec->opcode, spec->funct3, 1, 2, 16);
    assert(inst == 0x00208823);

    // Test beq x1, x2, 8 (B-type)
    // beq x1, x2, 8 (offset 8)
    // imm = 8: imm[12]=0, imm[11]=0, imm[10:5]=0, imm[4:1]=4
    // 0000000 00010 00001 000 01000 1100011
    spec = lookup_instruction("beq");
    inst = encode_b(spec->opcode, spec->funct3, 1, 2, 8);
    assert(inst == 0x00208463);
    
    // Test jal x1, 12 (J-type)
    // imm = 12: imm[20]=0, imm[10:1]=6, imm[11]=0, imm[19:12]=0
    // 00000000000000000000 00001 1101111 -> need to shuffle imm
    // inst = 000000001100 00000000 00001 1101111 => roughly 
    spec = lookup_instruction("jal");
    inst = encode_j(spec->opcode, 1, 12);
    assert(inst == 0x00C000EF);

    printf("All test_encode tests passed!\n");
}

int main() {
    test_encode();
    return 0;
}

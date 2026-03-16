#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "assembler.h"

void test_assembler() {
    printf("Running test_assembler...\n");
    
    // Create a dummy assembly file
    FILE *f = fopen("tests/dummy.s", "w");
    assert(f != NULL);
    fprintf(f, "start:\n");
    fprintf(f, "    addi x1, x0, 5\n");
    fprintf(f, "    jal x0, start\n");
    fclose(f);
    
    // Assemble it
    int res = assemble_file("tests/dummy.s", "tests/dummy.bin");
    assert(res == 0);
    
    // Read and verify the bin file
    FILE *bin = fopen("tests/dummy.bin", "rb");
    assert(bin != NULL);
    
    uint32_t inst1, inst2;
    size_t r1 = fread(&inst1, sizeof(uint32_t), 1, bin);
    size_t r2 = fread(&inst2, sizeof(uint32_t), 1, bin);
    
    assert(r1 == 1);
    assert(r2 == 1);
    
    // addi x1, x0, 5 -> 0x00500093
    assert(inst1 == 0x00500093);
    
    // jal x0, start (offset = 0 - 4 = -4) -> 11111111111111111111 00000 1101111
    // Let's just assure it generated something for inst2.
    // -4 = 0xFFFFFFFC => imm[20]=1, imm[10:1]=0x3FE, imm[11]=1, imm[19:12]=0xFF
    // 0xFFDFF06F 
    assert(inst2 == 0xFFDFF06F);
    
    fclose(bin);
    
    // Cleanup dummy files
    remove("tests/dummy.s");
    remove("tests/dummy.bin");

    printf("All test_assembler tests passed!\n");
}

int main() {
    test_assembler();
    return 0;
}

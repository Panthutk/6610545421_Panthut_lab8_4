#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "parser.h"

void test_parse_line() {
    ParsedLine out;
    int res;

    printf("Running test_parse_line...\n");

    // Test label + mnemonic + 3 operands
    res = parse_line("loop: add x1, x2, x3", &out);
    assert(res == 1);
    assert(strcmp(out.label, "loop") == 0);
    assert(strcmp(out.mnemonic, "add") == 0);
    assert(out.num_operands == 3);
    assert(strcmp(out.operands[0], "x1") == 0);
    assert(strcmp(out.operands[1], "x2") == 0);
    assert(strcmp(out.operands[2], "x3") == 0);

    // Test mnemonic + 2 operands (immediate)
    res = parse_line("addi x1, x0, 5", &out);
    assert(res == 1);
    assert(out.label[0] == '\0');
    assert(strcmp(out.mnemonic, "addi") == 0);
    assert(out.num_operands == 3);
    assert(strcmp(out.operands[0], "x1") == 0);
    assert(strcmp(out.operands[1], "x0") == 0);
    assert(strcmp(out.operands[2], "5") == 0);

    // Test label + mnemonic + memory operand format offset(rs1)
    res = parse_line("lw x3, 16(x2)", &out);
    assert(res == 1);
    assert(out.label[0] == '\0');
    assert(strcmp(out.mnemonic, "lw") == 0);
    assert(out.num_operands == 3); // x3, 16, x2
    assert(strcmp(out.operands[0], "x3") == 0);
    assert(strcmp(out.operands[1], "16") == 0);
    assert(strcmp(out.operands[2], "x2") == 0);

    // Test no operands
    res = parse_line("end: ret", &out);
    assert(res == 1);
    assert(strcmp(out.label, "end") == 0);
    assert(strcmp(out.mnemonic, "ret") == 0);
    assert(out.num_operands == 0);

    // Test empty line
    res = parse_line("   \t  ", &out);
    assert(res == 0);

    // Test comment line
    res = parse_line("   # this is a comment", &out);
    assert(res == 0);

    // Test line with trailing comment
    res = parse_line("add x1, x2, x3 # add them up", &out);
    assert(res == 1);
    assert(out.label[0] == '\0');
    assert(strcmp(out.mnemonic, "add") == 0);
    assert(out.num_operands == 3);

    printf("All test_parse_line tests passed!\n");
}

int main() {
    test_parse_line();
    return 0;
}

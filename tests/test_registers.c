#include <stdio.h>
#include <assert.h>
#include "registers.h"

void test_parse_register() {
    printf("Running test_parse_register...\n");

    // Test 'x' format
    assert(parse_register("x0") == 0);
    assert(parse_register("x5") == 5);
    assert(parse_register("x31") == 31);
    
    // Test invalid 'x' format
    assert(parse_register("x32") == -1);
    assert(parse_register("x-1") == -1);
    assert(parse_register("x") == -1);

    // Test ABI names
    assert(parse_register("zero") == 0);
    assert(parse_register("ra") == 1);
    assert(parse_register("sp") == 2);
    assert(parse_register("gp") == 3);
    assert(parse_register("tp") == 4);
    assert(parse_register("t0") == 5);
    assert(parse_register("t1") == 6);
    assert(parse_register("t2") == 7);
    assert(parse_register("s0") == 8);
    assert(parse_register("fp") == 8);
    assert(parse_register("s1") == 9);
    assert(parse_register("a0") == 10);
    assert(parse_register("a5") == 15);
    assert(parse_register("a7") == 17);
    assert(parse_register("s2") == 18);
    assert(parse_register("s11") == 27);
    assert(parse_register("t3") == 28);
    assert(parse_register("t6") == 31);

    // Test invalid names
    assert(parse_register("foo") == -1);
    assert(parse_register("123") == -1);
    assert(parse_register("") == -1);
    assert(parse_register(NULL) == -1);

    printf("All test_parse_register tests passed!\n");
}

int main() {
    test_parse_register();
    return 0;
}

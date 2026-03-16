#include <stdio.h>
#include <assert.h>
#include "symbols.h"

void test_symbols() {
    printf("Running test_symbols...\n");

    symbols_init();
    
    // Should not find an empty label
    assert(symbols_find("loop") == -1);
    
    // Add success
    assert(symbols_add("loop", 12) == 1);
    assert(symbols_add("start", 0) == 1);
    
    // Find success
    assert(symbols_find("loop") == 12);
    assert(symbols_find("start") == 0);
    
    // Add failure on duplicate label
    assert(symbols_add("loop", 24) == 0);
    assert(symbols_find("loop") == 12); // should still be 12
    
    // Add a couple more
    assert(symbols_add("end", 100) == 1);
    assert(symbols_find("end") == 100);
    
    // Init clears
    symbols_init();
    assert(symbols_find("loop") == -1);

    printf("All test_symbols tests passed!\n");
}

int main() {
    test_symbols();
    return 0;
}

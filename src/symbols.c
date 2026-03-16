#include "symbols.h"
#include <string.h>

static Symbol symbol_table[MAX_SYMBOLS];
static int num_symbols = 0;

void symbols_init(void) {
    num_symbols = 0;
}

int symbols_add(const char *label, int address) {
    if (!label || num_symbols >= MAX_SYMBOLS) return 0;
    
    // Check for duplicates
    if (symbols_find(label) != -1) return 0;
    
    strncpy(symbol_table[num_symbols].label, label, MAX_SYMBOL_LEN - 1);
    symbol_table[num_symbols].label[MAX_SYMBOL_LEN - 1] = '\0';
    symbol_table[num_symbols].address = address;
    
    num_symbols++;
    return 1;
}

int symbols_find(const char *label) {
    if (!label) return -1;
    
    for (int i = 0; i < num_symbols; i++) {
        if (strcmp(symbol_table[i].label, label) == 0) {
            return symbol_table[i].address;
        }
    }
    
    return -1;
}

#ifndef SYMBOLS_H
#define SYMBOLS_H

#define MAX_SYMBOLS 1024
#define MAX_SYMBOL_LEN 64

typedef struct {
    char label[MAX_SYMBOL_LEN];
    int address;
} Symbol;

/* Initialize the symbol table (clear all entries) */
void symbols_init(void);

/* Add a symbol to the table. Returns 1 on success, 0 if table is full or duplicate. */
int symbols_add(const char *label, int address);

/* Find a symbol's address. Returns the address, or -1 if not found. */
int symbols_find(const char *label);

#endif // SYMBOLS_H

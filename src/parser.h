#ifndef PARSER_H
#define PARSER_H

#define MAX_OPERANDS 4
#define MAX_LABEL_LEN 64
#define MAX_MNEMONIC_LEN 16
#define MAX_OPERAND_LEN 32

typedef struct {
    char label[MAX_LABEL_LEN];
    char mnemonic[MAX_MNEMONIC_LEN];
    char operands[MAX_OPERANDS][MAX_OPERAND_LEN];
    int num_operands;
} ParsedLine;

/* 
 * Parse a line of assembly code.
 * Extracts an optional label, a mnemonic, and operands.
 * Returns 1 on success, 0 if the line is empty or purely a comment.
 * Returns -1 on parsing error.
 */
int parse_line(const char *line, ParsedLine *out);

#endif // PARSER_H

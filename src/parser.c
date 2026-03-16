#include "parser.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static void trim_whitespace(char *str) {
    if (!str) return;
    char *end;

    // Trim leading space
    char *start = str;
    while(isspace((unsigned char)*start)) start++;
    
    // Shift string to beginning
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }

    if(*str == 0) return;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';
}

int parse_line(const char *line, ParsedLine *out) {
    if (!line || !out) return -1;

    // Initialize output
    out->label[0] = '\0';
    out->mnemonic[0] = '\0';
    out->num_operands = 0;
    for (int i = 0; i < MAX_OPERANDS; i++) {
        out->operands[i][0] = '\0';
    }

    // Work on a copy of the line to allow modification
    char buffer[256];
    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer)-1] = '\0';

    // Remove comments
    char *comment = strchr(buffer, '#');
    if (comment) {
        *comment = '\0';
    }

    trim_whitespace(buffer);
    if (buffer[0] == '\0') {
        return 0; // Empty line
    }

    char *ptr = buffer;

    // 1. Look for label
    char *colon = strchr(ptr, ':');
    if (colon) {
        *colon = '\0';
        strncpy(out->label, ptr, MAX_LABEL_LEN - 1);
        out->label[MAX_LABEL_LEN - 1] = '\0';
        trim_whitespace(out->label);
        
        ptr = colon + 1;
        trim_whitespace(ptr);
        
        if (*ptr == '\0') {
            return 1; // Line with only a label
        }
    }

    // 2. Extract mnemonic
    char *space = strpbrk(ptr, " \t");
    if (space) {
        *space = '\0';
        strncpy(out->mnemonic, ptr, MAX_MNEMONIC_LEN - 1);
        out->mnemonic[MAX_MNEMONIC_LEN - 1] = '\0';
        ptr = space + 1;
        trim_whitespace(ptr);
    } else {
        // No operands
        strncpy(out->mnemonic, ptr, MAX_MNEMONIC_LEN - 1);
        out->mnemonic[MAX_MNEMONIC_LEN - 1] = '\0';
        return 1;
    }

    // 3. Extract operands
    char *token = strtok(ptr, ",");
    while (token && out->num_operands < MAX_OPERANDS) {
        trim_whitespace(token);
        // Sometimes we get parenthesized operands like offset(rs1) for loads/stores
        // e.g., "16(x2)" -> operands should be "16" and "x2" or handled specially.
        // The lab pdf says: operands = ["x1","x2","loop"] for branches, 
        // For lb lbu lh lhu lw sb sh sw, an operand like 8(x2) is problematic for simple split.
        // Let's split on parentheses as well if present to simplify parsing.
        
        char *open_paren = strchr(token, '(');
        if (open_paren) {
            *open_paren = '\0';
            char *close_paren = strchr(open_paren + 1, ')');
            if (close_paren) {
                *close_paren = '\0';
            }
            
            trim_whitespace(token); // offset
            strncpy(out->operands[out->num_operands++], token, MAX_OPERAND_LEN - 1);
            
            char *reg = open_paren + 1;
            trim_whitespace(reg); // register
            if (out->num_operands < MAX_OPERANDS) {
                strncpy(out->operands[out->num_operands++], reg, MAX_OPERAND_LEN - 1);
            }
        } else {
            strncpy(out->operands[out->num_operands++], token, MAX_OPERAND_LEN - 1);
        }
        
        token = strtok(NULL, ",");
    }

    return 1;
}

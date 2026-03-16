#include "assembler.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.s> <output.bin>\n", argv[0]);
        return 1;
    }
    
    if (assemble_file(argv[1], argv[2]) != 0) {
        fprintf(stderr, "Assembly failed.\n");
        return 1;
    }
    
    return 0;
}

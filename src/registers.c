#include "registers.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    const char *abi_name;
    int reg_num;
} RegisterMap;

static const RegisterMap abi_registers[] = {
    {"zero", 0}, {"ra", 1}, {"sp", 2}, {"gp", 3}, {"tp", 4},
    {"t0", 5}, {"t1", 6}, {"t2", 7}, {"s0", 8}, {"fp", 8},
    {"s1", 9}, {"a0", 10}, {"a1", 11}, {"a2", 12}, {"a3", 13},
    {"a4", 14}, {"a5", 15}, {"a6", 16}, {"a7", 17}, {"s2", 18},
    {"s3", 19}, {"s4", 20}, {"s5", 21}, {"s6", 22}, {"s7", 23},
    {"s8", 24}, {"s9", 25}, {"s10", 26}, {"s11", 27}, {"t3", 28},
    {"t4", 29}, {"t5", 30}, {"t6", 31}
};

int parse_register(const char *name) {
    if (!name || name[0] == '\0') {
        return -1;
    }

    // Check for "xN" format where N is 0-31
    if (name[0] == 'x' && isdigit(name[1])) {
        char *endptr;
        long val = strtol(name + 1, &endptr, 10);
        if (*endptr == '\0' && val >= 0 && val <= 31) {
            return (int)val;
        }
    }

    // Check against ABI names
    int num_abi_regs = sizeof(abi_registers) / sizeof(abi_registers[0]);
    for (int i = 0; i < num_abi_regs; i++) {
        if (strcmp(name, abi_registers[i].abi_name) == 0) {
            return abi_registers[i].reg_num;
        }
    }

    return -1;
}

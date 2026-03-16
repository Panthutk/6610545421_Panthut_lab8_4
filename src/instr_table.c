#include "instr_table.h"
#include <string.h>

// Source: CS61C RV32I Reference Card
static const InstrSpec instr_table[] = {
    // Arithmetic (R-type)
    {"add",  FMT_R, 0x33, 0x0, 0x00},
    {"sub",  FMT_R, 0x33, 0x0, 0x20},
    {"sll",  FMT_R, 0x33, 0x1, 0x00},
    {"slt",  FMT_R, 0x33, 0x2, 0x00},
    {"sltu", FMT_R, 0x33, 0x3, 0x00},
    {"xor",  FMT_R, 0x33, 0x4, 0x00},
    {"srl",  FMT_R, 0x33, 0x5, 0x00},
    {"sra",  FMT_R, 0x33, 0x5, 0x20},
    {"or",   FMT_R, 0x33, 0x6, 0x00},
    {"and",  FMT_R, 0x33, 0x7, 0x00},
    
    // Immediate arithmetic (I-type)
    {"addi",  FMT_I, 0x13, 0x0, 0},
    {"slli",  FMT_I, 0x13, 0x1, 0},
    {"slti",  FMT_I, 0x13, 0x2, 0},
    {"sltiu", FMT_I, 0x13, 0x3, 0},
    {"xori",  FMT_I, 0x13, 0x4, 0},
    {"srli",  FMT_I, 0x13, 0x5, 0x00},
    {"srai",  FMT_I, 0x13, 0x5, 0x20},
    {"ori",   FMT_I, 0x13, 0x6, 0},
    {"andi",  FMT_I, 0x13, 0x7, 0},
    
    // Memory (I-type loads, S-type stores)
    {"lb",  FMT_I, 0x03, 0x0, 0},
    {"lh",  FMT_I, 0x03, 0x1, 0},
    {"lw",  FMT_I, 0x03, 0x2, 0},
    {"lbu", FMT_I, 0x03, 0x4, 0},
    {"lhu", FMT_I, 0x03, 0x5, 0},
    {"sb",  FMT_S, 0x23, 0x0, 0},
    {"sh",  FMT_S, 0x23, 0x1, 0},
    {"sw",  FMT_S, 0x23, 0x2, 0},
    
    // Control (B-type branches, J-type / I-type jumps)
    {"beq",  FMT_B, 0x63, 0x0, 0},
    {"bne",  FMT_B, 0x63, 0x1, 0},
    {"blt",  FMT_B, 0x63, 0x4, 0},
    {"bge",  FMT_B, 0x63, 0x5, 0},
    {"bltu", FMT_B, 0x63, 0x6, 0},
    {"bgeu", FMT_B, 0x63, 0x7, 0},
    {"jal",  FMT_J, 0x6f, 0x0, 0},
    {"jalr", FMT_I, 0x67, 0x0, 0},

    // Include lui / auipc just in case
    {"lui",   FMT_U, 0x37, 0x0, 0},
    {"auipc", FMT_U, 0x17, 0x0, 0}
};

const InstrSpec* lookup_instruction(const char *mnemonic) {
    if (!mnemonic) return NULL;
    
    int num_instr = sizeof(instr_table) / sizeof(instr_table[0]);
    for (int i = 0; i < num_instr; i++) {
        if (strcmp(mnemonic, instr_table[i].mnemonic) == 0) {
            return &instr_table[i];
        }
    }
    
    return NULL;
}

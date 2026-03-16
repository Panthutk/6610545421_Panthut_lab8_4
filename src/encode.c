#include "encode.h"

uint32_t encode_r(uint32_t opcode, uint32_t funct3, uint32_t funct7, int rd, int rs1, int rs2) {
    uint32_t inst = 0;
    inst |= (opcode & 0x7F);
    inst |= ((rd & 0x1F) << 7);
    inst |= ((funct3 & 0x7) << 12);
    inst |= ((rs1 & 0x1F) << 15);
    inst |= ((rs2 & 0x1F) << 20);
    inst |= ((funct7 & 0x7F) << 25);
    return inst;
}

uint32_t encode_i(uint32_t opcode, uint32_t funct3, int rd, int rs1, int imm) {
    uint32_t inst = 0;
    inst |= (opcode & 0x7F);
    inst |= ((rd & 0x1F) << 7);
    inst |= ((funct3 & 0x7) << 12);
    inst |= ((rs1 & 0x1F) << 15);
    inst |= ((imm & 0xFFF) << 20);
    return inst;
}

uint32_t encode_s(uint32_t opcode, uint32_t funct3, int rs1, int rs2, int imm) {
    uint32_t inst = 0;
    inst |= (opcode & 0x7F);
    inst |= ((imm & 0x1F) << 7);           // imm[4:0]
    inst |= ((funct3 & 0x7) << 12);
    inst |= ((rs1 & 0x1F) << 15);
    inst |= ((rs2 & 0x1F) << 20);
    inst |= (((imm >> 5) & 0x7F) << 25);   // imm[11:5]
    return inst;
}

uint32_t encode_b(uint32_t opcode, uint32_t funct3, int rs1, int rs2, int offset) {
    uint32_t inst = 0;
    inst |= (opcode & 0x7F);
    inst |= (((offset >> 11) & 0x1) << 7); // imm[11]
    inst |= (((offset >> 1) & 0xF) << 8);  // imm[4:1]
    inst |= ((funct3 & 0x7) << 12);
    inst |= ((rs1 & 0x1F) << 15);
    inst |= ((rs2 & 0x1F) << 20);
    inst |= (((offset >> 5) & 0x3F) << 25);// imm[10:5]
    inst |= (((offset >> 12) & 0x1) << 31);// imm[12]
    return inst;
}

uint32_t encode_u(uint32_t opcode, int rd, int imm) {
    uint32_t inst = 0;
    inst |= (opcode & 0x7F);
    inst |= ((rd & 0x1F) << 7);
    inst |= (imm & 0xFFFFF000);            // imm[31:12]
    return inst;
}

uint32_t encode_j(uint32_t opcode, int rd, int offset) {
    uint32_t inst = 0;
    inst |= (opcode & 0x7F);
    inst |= ((rd & 0x1F) << 7);
    inst |= (((offset >> 12) & 0xFF) << 12); // imm[19:12]
    inst |= (((offset >> 11) & 0x1) << 20);  // imm[11]
    inst |= (((offset >> 1) & 0x3FF) << 21); // imm[10:1]
    inst |= (((offset >> 20) & 0x1) << 31);  // imm[20]
    return inst;
}

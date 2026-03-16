#ifndef ENCODE_H
#define ENCODE_H

#include <stdint.h>

/* Encode R-type instruction
 * Layout: funct7(7) | rs2(5) | rs1(5) | funct3(3) | rd(5) | opcode(7)
 */
uint32_t encode_r(uint32_t opcode, uint32_t funct3, uint32_t funct7, int rd, int rs1, int rs2);

/* Encode I-type instruction
 * Layout: imm[11:0] | rs1(5) | funct3(3) | rd(5) | opcode(7)
 */
uint32_t encode_i(uint32_t opcode, uint32_t funct3, int rd, int rs1, int imm);

/* Encode S-type instruction 
 * Layout: imm[11:5] | rs2(5) | rs1(5) | funct3(3) | imm[4:0] | opcode(7)
 */
uint32_t encode_s(uint32_t opcode, uint32_t funct3, int rs1, int rs2, int imm);

/* Encode B-type instruction (Branch)
 * Layout: imm[12] | imm[10:5] | rs2(5) | rs1(5) | funct3(3) | imm[4:1] | imm[11] | opcode(7)
 */
uint32_t encode_b(uint32_t opcode, uint32_t funct3, int rs1, int rs2, int offset);

/* Encode U-type instruction
 * Layout: imm[31:12] | rd(5) | opcode(7)
 */
uint32_t encode_u(uint32_t opcode, int rd, int imm);

/* Encode J-type instruction (Jump)
 * Layout: imm[20] | imm[10:1] | imm[11] | imm[19:12] | rd(5) | opcode(7)
 */
uint32_t encode_j(uint32_t opcode, int rd, int offset);

#endif // ENCODE_H

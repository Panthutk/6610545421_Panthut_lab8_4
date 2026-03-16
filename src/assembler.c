#include "assembler.h"
#include "encode.h"
#include "instr_table.h"
#include "parser.h"
#include "registers.h"
#include "symbols.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int do_pass1(FILE *in) {
  char line[256];
  int pc = 0;
  ParsedLine pl;

  symbols_init();

  while (fgets(line, sizeof(line), in)) {
    int res = parse_line(line, &pl);
    if (res < 0)
      return -1;
    if (res == 0)
      continue;

    if (pl.label[0] != '\0') {
      if (!symbols_add(pl.label, pc)) {
        fprintf(stderr, "Error: Duplicate or invalid label: %s\n", pl.label);
        return -1;
      }
    }

    // If there's an instruction on this line, advance PC
    if (pl.mnemonic[0] != '\0') {
      pc += 4;
    }
  }
  return 0;
}

static int do_pass2(FILE *in, FILE *out) {
  char line[256];
  int pc = 0;
  ParsedLine pl;
  int line_num = 0;

  while (fgets(line, sizeof(line), in)) {
    line_num++;
    int res = parse_line(line, &pl);
    if (res <= 0)
      continue;

    if (pl.mnemonic[0] == '\0') {
      continue; // line with only a label
    }

    const InstrSpec *spec = lookup_instruction(pl.mnemonic);
    if (!spec) {
      fprintf(stderr, "Line %d: Unknown instruction: %s\n", line_num,
              pl.mnemonic);
      return -1;
    }

    uint32_t inst = 0;
    int rd = 0, rs1 = 0, rs2 = 0, imm = 0;

    // We will do very naive parsing here, assuming operands are valid
    // formatting e.g., R-type: rd, rs1, rs2 I-type: rd, rs1, imm (or for loads:
    // rd, imm, rs1) This usually depends on exactly how parser returns the
    // operands

    if (spec->format == FMT_R) {
      if (pl.num_operands >= 3) {
        rd = parse_register(pl.operands[0]);
        rs1 = parse_register(pl.operands[1]);
        rs2 = parse_register(pl.operands[2]);
      }
      inst = encode_r(spec->opcode, spec->funct3, spec->funct7, rd, rs1, rs2);
    } else if (spec->format == FMT_I) {
      // Check if arithmetic (e.g. addi x1, x2, 5 -> rd=x1, rs1=x2, imm=5)
      // Or load (e.g lw x1, 16(x2) -> rd=x1, imm=16, rs1=x2)
      if (pl.num_operands >= 3) {
        rd = parse_register(pl.operands[0]);
        if (parse_register(pl.operands[1]) != -1) {
          // addi style
          rs1 = parse_register(pl.operands[1]);
          imm = strtol(pl.operands[2], NULL, 0);
        } else {
          // load style (16, x2)
          imm = strtol(pl.operands[1], NULL, 0);
          rs1 = parse_register(pl.operands[2]);
        }
      } else if (pl.num_operands == 2) {
        // jalr x1, x2 is also FMT_I but with only 2 args maybe ? Or jalr
        // maybe 3. We'll skip edge cases for brevity if not strictly provided
      }
      inst = encode_i(spec->opcode, spec->funct3, rd, rs1, imm);
    } else if (spec->format == FMT_S) {
      // e.g. sb x2, 16(x1) -> parser gave rs2, imm, rs1
      if (pl.num_operands >= 3) {
        rs2 = parse_register(pl.operands[0]);
        imm = strtol(pl.operands[1], NULL, 0);
        rs1 = parse_register(pl.operands[2]);
      }
      inst = encode_s(spec->opcode, spec->funct3, rs1, rs2, imm);
    } else if (spec->format == FMT_B) {
      // beq rs1, rs2, label
      if (pl.num_operands >= 3) {
        rs1 = parse_register(pl.operands[0]);
        rs2 = parse_register(pl.operands[1]);
        const char *label = pl.operands[2];
        int target = symbols_find(label);

        if (target == -1) { // try as immediate
          imm = strtol(label, NULL, 0);
        } else {
          imm = target - pc;
        }
      }
      inst = encode_b(spec->opcode, spec->funct3, rs1, rs2, imm);
    } else if (spec->format == FMT_J) {
      // jal rd, label
      if (pl.num_operands >= 2) {
        rd = parse_register(pl.operands[0]);
        const char *label = pl.operands[1];
        int target = symbols_find(label);
        if (target == -1) { // try as immediate
          imm = strtol(label, NULL, 0);
        } else {
          imm = target - pc;
        }
      }
      inst = encode_j(spec->opcode, rd, imm);
    } else if (spec->format == FMT_U) {
      // lui rd, imm
      if (pl.num_operands >= 2) {
        rd = parse_register(pl.operands[0]);
        imm = strtol(pl.operands[1], NULL, 0);
      }
      inst = encode_u(spec->opcode, rd, imm);
    }

    fwrite(&inst, sizeof(uint32_t), 1, out);
    pc += 4;
  }

  return 0;
}

int assemble_file(const char *in_file, const char *out_file) {
  FILE *in = fopen(in_file, "r");
  if (!in) {
    perror("Failed to open input file");
    return -1;
  }

  if (do_pass1(in) != 0) {
    fclose(in);
    return -1;
  }

  rewind(in);

  FILE *out = fopen(out_file, "wb");
  if (!out) {
    perror("Failed to open output file");
    fclose(in);
    return -1;
  }

  int res = do_pass2(in, out);

  fclose(in);
  fclose(out);

  return res;
}

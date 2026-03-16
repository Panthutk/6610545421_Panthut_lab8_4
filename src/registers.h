#ifndef REGISTERS_H
#define REGISTERS_H

/* Parse a RISC-V register name and return its integer value (0-31).
 * Returns -1 if the name is invalid.
 * Accepts names like "x0"-"x31" and standard ABI names like "zero", "ra", "sp", etc.
 */
int parse_register(const char *name);

#endif // REGISTERS_H

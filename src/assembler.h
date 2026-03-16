#ifndef ASSEMBLER_H
#define ASSEMBLER_H

/* Assemble an input file into a binary output file.
 * Returns 0 on success, < 0 on error.
 */
int assemble_file(const char *in_file, const char *out_file);

#endif // ASSEMBLER_H

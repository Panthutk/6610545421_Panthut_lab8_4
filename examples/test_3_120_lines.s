# test_3_120_lines.s
# Extremely comprehensive assembler capability test

# Initialize Base
lui x1, 0x12345
addi x1, x1, 0x678
auipc x2, 0xabcd0

# Basic R-Type tests
add x3, x1, x2
sub x4, x1, x2
sll x5, x1, x2
slt x6, x1, x2
sltu x7, x1, x2
xor x8, x1, x2
srl x9, x1, x2
sra x10, x1, x2
or x11, x1, x2
and x12, x1, x2

# Basic I-Type tests
addi x3, x1, 0x123
slli x5, x1, 0x12
slti x6, x1, 0x123
sltiu x7, x1, 0x123
xori x8, x1, 0x123
srli x9, x1, 0x12
srai x10, x1, 0x12
ori x11, x1, 0x123
andi x12, x1, 0x123

# Memory Tests
lui sp, 0x20000
sw x1, 0(sp)
sh x2, 4(sp)
sb x3, 6(sp)

lw x13, 0(sp)
lh x14, 4(sp)
lhu x15, 4(sp)
lb x16, 6(sp)
lbu x17, 6(sp)

# Branches - Forward 
beq x1, x2, b_eq
bne x1, x2, b_ne
blt x1, x2, b_lt
bge x1, x2, b_ge
bltu x1, x2, b_ltu
bgeu x1, x2, b_geu

# Landing pads for branches
b_eq: addi x20, x0, 1
b_ne: addi x20, x0, 2
b_lt: addi x20, x0, 3
b_ge: addi x20, x0, 4
b_ltu: addi x20, x0, 5
b_geu: addi x20, x0, 6

# Backwards Branches
loop_start:
addi x21, x21, 1
blt x21, x20, loop_start

# Jumps
jal x1, jump_target
addi x22, x0, 1        # Skip this
jump_target:

lui x23, 0x12345
# We don't guarantee full support for jalr with offset in basic parser but let's test a simple one
jalr x0, x23, 0

# Random sequence to pad lines and test everything
add a0, a1, a2
sub a3, a4, a5
sll a6, a7, t0   # testing parser case? Actually our parser is case sensitive right now. So lowercase only.
sll a6, a7, t0
slt t1, t2, t3
sltu t4, t5, t6
xor s0, s1, s2
srl s3, s4, s5
sra s6, s7, s8
or s9, s10, s11
and a0, a1, a2

addi s0, s0, 1
slli s1, s1, 2
slti s2, s2, 3
sltiu s3, s3, 4
xori s4, s4, 5
srli s5, s5, 6
srai s6, s6, 7
ori s7, s7, 8
andi s8, s8, 9

lui t0, 0x80000
lw t1, 0(t0)
sw t2, 4(t0)
lh t3, 8(t0)
sh t4, 12(t0)
lb t5, 16(t0)
sb t6, 20(t0)
lbu a0, 24(t0)
lhu a1, 28(t0)

bne a0, a1, last_target
last_target:

add t0, x0, x0
add t1, x0, x0
add t2, x0, x0
add t3, x0, x0
add t4, x0, x0
add t5, x0, x0
add t6, x0, x0

# Some final infinite loop to end
final_end:
jal x0, final_end

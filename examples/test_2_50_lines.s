# test_2_50_lines.s
# Simulates a basic string length calculation and char substitution
# Uses R-type, I-type, S-type, B-type, U-type, J-type instructions

start:
    addi x10, x0, 0x41      # 'A'
    addi x11, x0, 0x42      # 'B'
    addi x12, x0, 0x43      # 'C'
    addi x13, x0, 0x00      # '\0'
    
    # store a string "ABC"
    lui x5, 0x10000         # base address
    sb x10, 0(x5)
    sb x11, 1(x5)
    sb x12, 2(x5)
    sb x13, 3(x5)           # null terminator
    
    # String length routine
    addi x6, x5, 0          # current ptr
    addi x7, x0, 0          # length
    
strlen_loop:
    lb x8, 0(x6)
    beq x8, x0, strlen_done
    addi x7, x7, 1
    addi x6, x6, 1
    jal x0, strlen_loop
    
strlen_done:
    # We now have length = 3 in x7
    
    # String substitution routine: replace 'B' with 'Z' (0x5A)
    addi x6, x5, 0          # reset ptr
    addi x9, x0, 0x5A       # 'Z'
    
replace_loop:
    lb x8, 0(x6)
    beq x8, x0, end         # if null, end
    bne x8, x11, skip_replace
    sb x9, 0(x6)            # if 'B', replace with 'Z'
skip_replace:
    addi x6, x6, 1
    jal x0, replace_loop

    # Just some filler ALU instructions
    add x20, x10, x11
    sub x21, x12, x10
    sll x22, x20, x21
    srl x23, x22, x21
    sra x24, x23, x21
    slt x25, x10, x11
    sltu x26, x10, x11
    xor x27, x10, x11
    or x28, x10, x11
    and x29, x10, x11
    
    # I-type ALUs
    slli x30, x29, 2
    srli x31, x30, 1
    srai x1, x31, 1
    
end:
    jal x0, end

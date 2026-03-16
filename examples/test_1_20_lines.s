# A simple RISC-V program with 20+ lines
# Computes the sum of array [1..10]
start:
    addi x1, x0, 10      # array size
    addi x2, x0, 1       # current val (1)
    addi x3, x0, 0       # sum
    lui x4, 0x10000      # base address
    addi x5, x0, 0       # index
    
loop_init:
    sw x2, 0(x4)         # store val to mem
    addi x4, x4, 4       # increment address
    addi x2, x2, 1       # increment val
    addi x5, x5, 1       # increment index
    blt x5, x1, loop_init # if idx < 10, repeat
    
    lui x4, 0x10000      # reset address
    addi x5, x0, 0       # reset index
    
sum_loop:
    lw x6, 0(x4)         # load val
    add x3, x3, x6       # sum += val
    addi x4, x4, 4       # increment address
    addi x5, x5, 1       # increment index
    blt x5, x1, sum_loop # if idx < 10, repeat
    
end:
    jal x0, end          # infinite loop terminator

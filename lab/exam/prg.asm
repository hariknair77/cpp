A DB 0
C EQU 100
LDI R0,C
PUSH R0
POP R1
ADD R2.R0,R1
MUL R3,R2,R1
SUB R15,R15,R15
JZ R4,L1
JGTZ R4,L1
JLTZ R4,L1
HALT HLT
LD R10,A
DIV R11,R10,R0
RET
L1 ST R0,A
MUL R14,R13,R12
JNZ R0,HALT
END
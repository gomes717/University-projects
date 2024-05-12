; @file    main.s
; @authors Hadryan Salles
;          Guilherme Gomes
; @brief   assignment 1 of micro control systems
; @created 06/22/2021
; initially taken from:
; Exemplo.s
; Desenvolvido para a placa EK-TM4C1294XL
; Prof. Guilherme Peron
; 12/03/2018

; cortex-m4 uses thumb-2 instructions, with mixed 16 and 32 bits instructions
	THUMB  

; EQU defines
; <name> EQU <value>

; variables data area
	AREA DATA, ALIGN=2
; export variables to other files
; EXPORT <var> [DATA, SIZE=<size>]
; declare a variable from the first ram's position
; <var> SPACE <tam>

; code area
	AREA |.text|, CODE, READONLY, ALIGN=2
; export functions to other files
	EXPORT Start
; import functions from other files
; IMPORT <func> 

; addressing modes:
	; - immediate: the value is preceded by '#'
		; #25     : decimal 25
		; #0x2F   : hex 2F
		; #2_1101 : binary 1101
	; - register: the value is preceded by 'R'
		; MOV R0, R1 ; R0 <= R1
	; - scaled: offset the register by some value
		; MOV R0, R1, LSL #3 ; R0 <= (R1 << 3) 
		; MOV R0, R1, LSR #3 ; R0 <= (R1 >> 3) = (R1 / 2^3) unsigned 
		; MOV R0, R1, ASR #3 ; R0 <= (R1 >> 3) = (R1 / 2^3) signed
	; - indexed: registers are like pointers to memory
		; LDR R0, [R1]      ; R0 <= [R1]
		; LDR R0, [R1 + #4] ; R0 <= [R1 + 4]
	; - relative: used when modifying the PC, branches, functions calls, ROM
		; B label ; jump to label

; operand2:
	; the second operand of all instructions
	; either an immediate value or a register
	; when it's a register, it can:
		; be logically shifted to the right or left with LSR or LSL
		; be arithmetically shifted to the right with ASR
		; be logicallly rotated to the right with ROR

; RAM access instructions
	; only accessed by LDR or STR
	; LDR read data from RAM
	; STR store data into RAM
	; we need a register to index the RAM
	; examples:
		; LDR R4, [R0] ; R4   <= [R0]
		; STR R3, [R0] ; [R0] <= R3
	; we can use offset, pre-indexed or post-indexed
	; with offset:
		; LDR R4, [R1, #8] ; R4 <= [R1 + 8]
	; pre-indexed, we increment the address before the operation:
		; LDR R0, [R1, #2]! ; R0 <= [R1 + 2], R1 <= R1 + 2
		; STR R2, [R3, R4]! ; [R3 + R4] <= R2, R3 <= R3 + R4
	; post-indexed, we increment the address after the operation:
		; LDR R0, [R1], #8 ; R0 <= [R1], R1 <= R1 + 8
	; we can also inform the type of the data (optional)
		; LDR{type} R0 ....
	; the type can be:
		; ' '  : 32 bits
		; 'B'  :  8 bits unsigned 
		; 'SB' :  8 bits signed
		; 'H'  : 16 bits unsigned
		; 'D'  : 64 bits using two registers
		; ...
	; example:
		; LDRB R4, [R0] ; read only one byte at [R0]

; transfer instructions
	; MOV{S} Rd, <op2> ; set Rd to the value specified by <op2>
	; MVN{S} Rd, <op2> ; performs a bitwise logical NOT on <op2> before moving it 
	; to move constants with more than 16 bits we can use:
		; MOV and MOVT, where MOVT access the MSB 16 bits of the register
			; MOVT Rd, <op2> ; move <op2> to the 16 MSB of Rd
		; using Keil pseudo instruction
			; LDR R6, Pi
			; defining Pi constant outside of the executing code
			; Pi DCD 314159
			; or
			; LDR R6, =314159

; logical operations
	; bitwise
	; AND{S}{cond} {Rd, } Rn, <op2> ; Rd = Rn & op2
	; ORR{S}{cond} {Rd, } Rn, <op2> ; Rd = Rn | op2
	; EOR{S}{cond} {Rd, } Rn, <op2> ; Rd = Rn ^ op2
	; BIC{S}{cond} {Rd, } Rn, <op2> ; Rd = Rn & (~op2)
	; ORN{S}{cond} {Rd, } Rn, <op2> ; Rd = Rn | (~op2)
	; NEG{S}{cond} {Rd, } Rn        ; Rd = ~Rn 
	; if we put S, the flags N and Z are updated

; shift operations
	; 2 inputs and 1 output
	; LSR{S} 
	; logical shift to the right
	; it's like unsigned division by 2^n
	; zeros are inserted into the n blank MSb 
	; so negative numbers became positive
	; if we put S, the carry flag is updated with the n LSb
	; ASR{S}
		; arithmetic shift to the right
		; signed division by 2^n
		; the MSB is copied to each one of the n blank spaces
		; if we put S, the carry flag is updated with the n LSb
	; LSL{S}
		; logical shift to the left
		; unsigned multiplication by 2^n
		; zeros are inserted into the n blank LSb
		; if we put S, the carry flag is updated with the n MSb
	; ROR{S}
		; rotation to right
		; no rotation to left because it's equivalent to a ROR with 32-n
		; the n LSbits are inserted into the n MSbits
		; if we put S, the carry flag is updated with the n LSb
	; RRX{S}
		; rotation to the right of only 1 bit
		; the MSb became the bit inside the carry flag
		; if we put S, the carry flag is updated with the LSb

; arithmetic operations
	; executed by digital hardware
	; sum, sub, mul, div and comparison
	; carry:
		; for sums, 0 if the sum fitted 32 bits and 1 if it didn't
		; for subs, 1 if the result is positive and 0 if it's negative
	; overflow:
		; signed or not
		; V-bit is setted when pass between 0x8000000 and 0x7FFFFFFF 
	; ADD{S}{cond} {Rd, } Rn, <op2>
	; ADC{S}{cond} {Rd, } Rn, <op2> ; Rd = Rn + op2 + C
	; SUB{S}{cond} {Rd, } Rn, <op2> ; Rd = Rn - op2
	; RSB{S}{cond} {Rd, } Rn, <op2> ; Rd = op2 - Rn
	; there is also versions of these ^^ instructions with #im12
	; CMP{cond} Rn, <op2> ; Rn - op2
	; CMN{cond} Rn, <op2> ; Rn - (-op2)
	; CMP and CMN just serve to comparisons of if-then and loops
	; for 32 bits results
		; MUL{S}{cond} {Rd, } Rn, Rm ; Rd = Rn * Rm
		; MLA{cond} Rd, Rn, Rm, Ra   ; Rd = Ra + Rn*Rm
		; MLS{cond} Rd, Rn, Rm, Ra   ; Rd = Ra - Rn*Rm
		; UDIV{cond} {Rd, } Rn, Rm   ; Rd = Rn / Rm (unsigned)
		; SDIV{cond} {Rd, } Rn, Rm   ; Rd = Rn / Rm (signed)
	; for 64 bits results
		; UMULL{cond} RdLo, RdHi, Rn, Rm ; Rd = Rn * Rm
		; SMULL{cond} RdLo, RdHi, Rn, Rm ; Rd = Rn * Rm
		; UMLAL{cond} RdLo, RdHi, Rn, Rm ; Rd = Rd + Rn * Rm
		; SMLAL{cond} RdLo, RdHi, Rn, Rm ; Rd = Rd + Rn * Rm

; if-then block
	; IT{x{y{z}}} {cond}
		; x specifies a condition for the second instruction (T or E)
		; y specifies a condition for the third  instruction (T or E)
		; z specifies a condition for the forth  instruction (T or E)
	; ITTE NE
		; ANDNE  R0, R0, R1 ; if NE
		; ADDSNE R0, R0, R1 ; if NE
		; MOVEQ  R0, R0, R1 ; else
	; the instructions inside the block ends with the same condition 
	; conditions test the flags
	; EQ, NE, CS, HS, MI, PL, VS, VC
	; HI, LS, GE, LT, GT, LE, AL
	; branche instructions are only allowed as the last instruction of the block
	; some instructions can't be used inside if-then blocks:
		; IT, CBZ, CBNZ, CPSIE, CPSID

; stack instructions
	; only 2 instructions
	; it's inside the RAM
	; from 0x2000.0000 to 0x2000.7FFC
	; stack pointer always point to the stack top
	; as we push into the stack, the stack pointer decrements
	; PUSH <reglist>
	; POP  <reglsit>
	; <reglist> : list of registers separeted by ',' inside {}
	; good practice to avoid reglist and push/pop individually

; branch instructions
	; B{cond} label  ; jump to the label
	; BL{cond} label ; jump to subroutine in the label
	; BX{cond} Rm    ; jump to location specified by Rm
	; BL it's like the fuction call and BX the function return
	; BL stores the PC before jumping into the LR
	; then we can jump back to LR after finishing the function
	; we have to take care of function calls in sequence by saving the LR
	; we can use the stack to save the LR
	; B{cond} doesn't need to be inside if-then block
	; CBZ Rn, <label> ; compare and jump if zero
	; CBNZ Rn, <label> ; compare and jump if not zero

; directives 
	; CODE: machine instructions space (ROM)
	; DATA: global variables space (RAM)
	; STACK: stack space (RAM)
	; ALIGN=n: start the section with alignment for 2^n bytes
	; |.text|: sections of the code generated by the C compiler
		; allows the assembly code to be called from C
	; NOINIT: declare an area of the RAM to not be initialized
	; DCB, DCW and DCD are used to declare 8, 16 and 32-bits variables into memory
	; SPACE size ; can also be used to reserve size bytes, unitialized
		; vector_name SPACE 5 
		; LDR R0, =vector_name
	; EQU it's like the C define
		; EXAMPLE_PORT EQU 0x400073FC

; main
Start
	; memory access exercices
	MOV  R0, #65       ; R0 <= 65
	MOV  R1, #0x1B00   ; R1[ 0:15] <= 0x1B00
	MOVT R1, #0x1B00   ; R1[16:31] <= 0x1B00
	MOV  R2, #0x5678   ; R2[ 0:15] <= 0x5678
	MOVT R2, #0x1234   ; R2[16:31] <= 0x1234
	MOV  R3, #0x40     ; R3[ 0:15] <= 0x40
	MOVT R3, #0x2000   ; R3[16:31] <= 0x2000
	STR  R0, [R3]      ; [R3] <= R0
	STR  R1, [R3, #4]  ; [R3 + 4] <= R1
	STR  R2, [R3, #8]  ; [R3 + 8] <= R2
	MOV  R4, #0x1      ; R4[ 0:15] <= 0x1
	MOVT R4, #0xF      ; R4[16:31] <= 0xF
	STR  R4, [R3, #12] ; [R3 + 12] <= R4
	MOV  R5, #0xCD     ; R5 <= 0xCD
	STRB R5, [R3, #6]  ; [R3 +  6][0:7] <= R5
	LDR  R7, [R3]      ; R7 <= [R3]
	LDR  R8, [R3, #8]  ; R8 <= [R3 + 8]
	MOV  R9, R7        ; R9 <= R7
	; logical operations exercices
	MOV  R0, #0xF0           ; R0 <= 0xF0
	ANDS R0, R0, #2_01010101 ; R0 <= R0 & 0b01010101
	MOV  R1, #2_11001100     ; R1 <= 0b11001100
	ANDS R1, R1, #2_00110011 ; R1 <= R1 & 0b00110011
	MOV  R2, #2_10000000     ; R2 <= 0b10000000
	ORRS R2, R2, #2_00110111 ; R2 <= R2 | 0b00110111
	MOV  R3, #0xABCD         ; R3[ 0:15] <= 0xABCD
	MOVT R3, #0xABCD         ; R3[16:31] <= 0xABCD
	MOV  R4, #0xFFFF         ; R4 <= 0xFFFF
	BICS R3, R3, R4          ; R3 <= R3 & (~R4)
	; shift operations exercices
	MOV  R0, #701    ; R0 <= 701
	LSRS R1, R0, #5  ; R1 <= R0 >> 5 logical
	MOV  R2, #32067  ; R2 <= 32067
	NEG  R2, R2      ; R2 <= ~R2
	LSRS R3, R2, #4  ; R3 <= R2 >> 4 logical
	ASRS R4, R1, #3  ; R4 <= R1 >> 3 arithmetic
	ASRS R5, R2, #5  ; R5 <= R2 >> 5 arithmetic
	MOV  R6, #255    ; R6 <= 255
	LSLS R6, R6, #8  ; R6 <= R6 << 8
	MOV  R7, #58982  ; R7 <= 58982
	NEG  R7, R7      ; R7 <= ~R7
	LSLS R7, R7, #18 ; R7 <= R7 << 18
	MOV  R8, #0x1234 ; R8[0:15] <= 0x1234
	MOVT R8, #0xFABC ; R8[16:31] <= 0xFABC
	ROR  R8, R8, #10 ; R8 <= R8 <> 10
	MOV  R9, #0x4321 ; R9 <= 0x4321
	RRX  R9, R9      ; R9 <= <>R9
	RRX  R9, R9      ; R9 <= <>R9
	; arithmetic operations exercices
	MOV  R0, #101    ; R0 <= 101
	ADDS R0, #253    ; R0 <= R0 + 253 (w/ flags)
	MOV  R1, #40543  ; R1 <= 40543
	ADD  R1, #1500   ; R1 <= R1 + 1500
	MOV  R2, #340    ; R2 <= 340
	SUBS R2, #123    ; R2 <= R2 - 123 (w/ flags)
	MOV  R3, #1000   ; R3 <= 1000
	SUBS R3, #2000   ; R3 <= R3 - 2000 (w/ flags)
	MOV  R4, #54378  ; R4 <= 54378
	MOV  R9, #4      ; R9 <= 4
	MUL  R4, R9      ; R4 <= R4 * R9 (same as R4 << 2)
	MOV  R5, #0x3344 ; R5[ 0:15] <= 0x3344
	MOVT R5, #0x1122 ; R5[16:31] <= 0x1122
	MOV  R6, #0x2211 ; R6[ 0:15] <= 0x2211
	MOVT R6, #0x4433 ; R6[16:31] <= 0x4433
	UMULL R7, R8, R5, R6 ; R7 <= R5*R6[0:15] and R8 <= R5*R6[16:31]
	MOV   R9, #0x7560    ; R9[ 0:15] <= 0x7560
	MOVT  R9, #0xFFFF    ; R9[16:31] <= 0xFFFF
	MOV   R10, #0x1000   ; R10 <= 1000
	SDIV  R11, R9, R10   ; R11 <= R9 / R10 (signed)
	UDIV  R12, R9, R10   ; R12 <= R9 / R10 (unsigned)
	; conditional operations exercices
	MOV   R0, #10     ; R0 <= 10
	CMP   R0, #9      ; compare R0 and 9
	ITTE  GE          ; if R0 >= 9
	MOVGE R1, #50     ; R1 <= 50
	ADDGE R2, R1, #32 ; R2 <= R1 + 32
	MOVLT R3, #75     ; else R3 <= 75
	CMP   R0, #11     ; compare R0 and 9
	ITTE  GE          ; if R0 >= 9
	MOVGE R1, #50     ; R1 <= 50
	ADDGE R2, R1, #32 ; R2 <= R1 + 32
	MOVLT R3, #75     ; else R3 <= 75
	; stack operations exercices
	MOV  R0, #10     ; R0 <= 10
	MOV  R1, #0xCC22 ; R1[ 0:15] <= 0xCC22
	MOVT R1, #0xFF11 ; R1[16:31] <= 0xFF11
	MOV  R2, #1234   ; R2 <= 1234
	MOV  R3, #0x300  ; R3 <= 0x300
	PUSH {R0}        ; push R0
	PUSH {R1}        ; push R1
	PUSH {R2}        ; push R2
	PUSH {R3}        ; push R3
	MOV  R1, #60     ; R1 <= 60
	MOV  R2, #0x1234 ; R2 <= 0x1234
	POP  {R3}        ; pop R3
	POP  {R2}        ; pop R2
	POP  {R1}        ; pop R1
	POP  {R0}        ; pop R0
	; branch operations exercices
	; MOV R0, #10    ; R0 <= 10
; add_five
	; ADD R0, R0, #5 ; R0 <= R0 + 5
	; CMP R0, #50    ; compare R0 and 50
	; BNE add_five   ; jump to add_five if R0 != 50
	; BL  func       ; jump to func
	; NOP            ; nop
; end	B   end        ; jump to end
; func
	; MOV   R1, R0  ; R1 <= R0
	; CMP   R1, #50 ; compare R1 and 50
	; ITE   LT      ; if R1 < 50
	; ADDLT R1, #1  ; R1 <= R1 + 1
	; MVNGE R1, #50 ; else R1 <= -50
	; BX    LR      ; return
	; directives exercices
	MOV R1, #4     ; R1 <= 4
	MOV R0, #1     ; R0 <= 1
fat MUL R0, R0, R1 ; R0 <= R0 * R1
	SUB R1, R1, #1 ; R1 <= R1 - 1
	CMP R1, #1     ; compare R1 and 1
	BGT fat        ; jump to fat if R1 > 1
	NOP 

	ALIGN ; align the end of this section 
	END   ; end of this file
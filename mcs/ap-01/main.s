; @file    main.s
; @authors Hadryan Salles
;          Guilherme Gomes
; @brief   assignment 2 of micro control systems
; @created 07/04/2021
; initially taken from:
; Exemplo.s
; Desenvolvido para a placa EK-TM4C1294XL
; Prof. Guilherme Peron
; 12/03/2018

; cortex-m4 uses thumb-2 instructions, with mixed 16 and 32 bits instructions
	THUMB  

; EQU defines
BASE EQU 0x20000400
PRIM EQU 0x20000500
; <name> EQU <value>

; variables data area
	AREA DATA, ALIGN=2
; export variables to other files
; EXPORT <var> [DATA, SIZE=<size>]
; declare a variable from the first ram's position
; <var> SPACE <tam>

; code area
	AREA |.text|, CODE, READONLY, ALIGN=2
RANDONS DCB 193, 63, 176, 127, 43, 13, 211, 3, 203, 5, 21, 7, 206, 245, 157, 237, 241, 105, 252, 19
; export functions to other files
	EXPORT Start
; import functions from other files

; main
Start
	; setup base addresses
	LDR  R0, =BASE
	LDR  R2, =BASE
	LDR  R3, =PRIM 
	LDR  R4, =PRIM 
	LDR  R5, =PRIM
	LDR  R6, =PRIM
	LDR  R7, =RANDONS
	MOV  R8, #0
	MOV  R9, #20
insert_randons
	CMP  R8, R9         ; compare R8 and R9
	BEQ  prime_test     ; jump to prime test if R8 >= R9
	LDRB R1, [R7], #1   ; load the value in the ROM
	STRB R1, [R0], #1   ; store the value in the RAM
	ADD  R8, #1         ; increment the iterator
	B    insert_randons ; jump to insert the next value
prime_test
	CMP  R2, R0
	BGE  sort            ; if already processed all numbers, go to sort
	LDRB R10, [R2], #1   ; R10 <= [R2], R2 <= R2 + 1 
	CMP  R10, #1         ; compare R10 and 1
	BLE  prime_test      ; if R10 == 1, then it's not prime
	MOV  R9, #2          ; R9 <= 2
div_test
	CMP  R9, R10         ; compare R9 and R10
	BGE  insert          ; insert the number if the div_counter reached it
	UDIV R8, R10, R9     ; R8 <= R10 / R9
	MLS  R8, R9, R8, R10 ; R8 <= R10 - R9*R8
	CMP  R8, #0          ; compare R8 and 0
	BEQ  prime_test      ; if the remain of R10/R9 is zero, the number isn't prime
	ADD  R9, #1          ; R9 <= R9 + 1
	B    div_test        ; after incremented div_counter, go test the division again
insert
	STRB R10, [R3], #1   ; store the number in the prime list using post indexed
	B    prime_test      ; go to test the next number
sort
	SUB    R3, #1          ; R3 <= R3 - 1
	CMP    R3, R6          ; compare R3 and R6
	BLE    end             ; jump to end if R3 <= R6
	MOV    R4, R6          ; R4 <= R6
bubble
	LDRB   R8, [R4]        ; R8 <= [R4]
	LDRB   R9, [R4, #1]    ; R9 <= [R4 + 1]
	CMP    R8, R9          ; compare R6 and R7
	ITT    GT              ; if then block
	STRBGT R9, [R4]        ; [R4]     <= R9 if R8 > R9
	STRBGT R8, [R4, #1]    ; [R4 + 1] <= R8 if R8 > R9
	ADD    R4, R4, #1      ; R4 <= R4 + 1
	CMP    R4, R3          ; compare R4 and R3
	BGE    sort            ; jump to sort if R4 >= R3
	B      bubble          ; otherwise jump to bubble 
end
	NOP
	ALIGN ; align the end of this section 
	END   ; end of this file
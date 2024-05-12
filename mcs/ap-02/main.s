; main.s
; Desenvolvido para a placa EK-TM4C1294XL
; Prof. Guilherme Peron
; 24/08/2020
; Este programa espera o usu�rio apertar a chave USR_SW1.
; Caso o usu�rio pressione a chave, o LED1 piscar� a cada 0,5 segundo.

; -------------------------------------------------------------------------------
        THUMB                        ; Instru��es do tipo Thumb-2
; -------------------------------------------------------------------------------
		
; Declara��es EQU - Defines
;<NOME>         EQU <VALOR>
; ========================

; -------------------------------------------------------------------------------
; �rea de Dados - Declara��es de vari�veis
		AREA  DATA, ALIGN=2
		; Se alguma vari�vel for chamada em outro arquivo
		;EXPORT  <var> [DATA,SIZE=<tam>]   ; Permite chamar a vari�vel <var> a 
		                                   ; partir de outro arquivo
;<var>	SPACE <tam>                        ; Declara uma vari�vel de nome <var>
                                           ; de <tam> bytes a partir da primeira 
                                           ; posi��o da RAM		

; -------------------------------------------------------------------------------
; �rea de C�digo - Tudo abaixo da diretiva a seguir ser� armazenado na mem�ria de 
;                  c�digo
        AREA    |.text|, CODE, READONLY, ALIGN=2

		; Se alguma fun��o do arquivo for chamada em outro arquivo	
        EXPORT Start                ; Permite chamar a fun��o Start a partir de 
			                        ; outro arquivo. No caso startup.s
									
		; Se chamar alguma fun��o externa	
        ;IMPORT <func>              ; Permite chamar dentro deste arquivo uma 
									; fun��o <func>
		IMPORT  PLL_Init
		IMPORT  SysTick_Init
		IMPORT  SysTick_Wait1ms			
		IMPORT  GPIO_Init
        IMPORT  PortN_Output
		IMPORT  PortF_Output	
        IMPORT  PortJ_Input	


; -------------------------------------------------------------------------------
; main()
Start  		
	BL PLL_Init
	BL SysTick_Init
	BL GPIO_Init
	MOV R4, #0      ; modo incial
	MOV R5, #1000   ; tempo inicial
	MOV R6, #2_1000 ; estado cavaleiro
	MOV R7, #1      ; 0 se cavaleiro estiver andando para esquerda
	MOV R8, #2_0000 ; estado contador
	MOV R9, #2_0000 ; dado usado para acender leds
MainLoop
	BL    PortJ_Input
Verifica_Nenhum
	CMP	  R0, #2_11
	BNE   Verifica_SW1
	B     LoopCavaleiro
Verifica_SW1
	CMP	  R0, #2_10
	BNE   Verifica_SW2
	BL    AlternaModo
	B     LoopCavaleiro
Verifica_SW2	
	CMP   R0, #2_01
	BNE   Verifica_Ambos
	BL    AlternaVelocidade
	B     LoopCavaleiro
Verifica_Ambos	
	CMP   R0, #2_00
	BNE   LoopCavaleiro
	BL    AlternaModo
	BL    AlternaVelocidade
LoopCavaleiro
	CMP	  R4, #0
	BNE   LoopContador
	MOV   R9, R6 
	BL    Acender
	CMP   R7, #0
	BNE   CavaleiroDireita
	CMP   R6, #2_1000 ; verifica se cavaleiro chegou no ultimo bit à esquerda
	ITTE  EQ
	MOVEQ R7, #1      ; se sim, inverte o estado e anda para direita
	MOVEQ R6, #2_0100
	LSLNE R6, R6, #1  ; shifta o valor para a esquerda, deslizando o bit
	B     MainLoop  
CavaleiroDireita
	CMP   R6, #2_0001
	ITTE  EQ          ; verifica se cavaleiro chegou no ultimo bit à direita
	MOVEQ R7, #0
	MOVEQ R6, #2_0010 ; se sim, inverte o estado e anda para esquerda
	LSRNE R6, R6, #1
	B     MainLoop
LoopContador
	MOV   R9, R8
	BL    Acender
	CMP   R8, #2_1111
	ITE   EQ
	MOVEQ R8, #2_0000
	ADDNE R8, R8, #1
	B     MainLoop

Acender
	PUSH {LR}
	LSR  R0, R9, #2      ; R0 = R1 >> 2
	BL   PortN_Output
	MOV  R0, R9
	BIC  R0, #2_11111101 ; filtro apenas o bit 1
	LSL  R0, R0, #3      ; movo o bit 1 para o bit 4
	MOV  R2, R9
	BIC  R2, #2_11111110 ; filtro apenas o bit 0
	ORR  R0, R0, R2      ; junto esses dois bits fazendo o OR
	BL   PortF_Output
	MOV  R0, R5
	BL   SysTick_Wait1ms
	POP  {LR}
	BX   LR

AlternaModo
	PUSH  {LR}
	CMP   R4, #1
	ITE   EQ
	MOVEQ R4, #0
	MOVNE R4, #1
	BL    EsperaSoltar
	POP   {LR}
	BX   LR			

AlternaVelocidade
    PUSH {LR}
Verifica500
	CMP  R5, #500
	BNE  Verifica200
	MOV  R5, #200
	B    FimAlternaVelocidade
Verifica200
	CMP  R5, #200
	BNE  Verifica1000
	MOV  R5, #1000
	B    FimAlternaVelocidade
Verifica1000
	MOV  R5, #500
	B    FimAlternaVelocidade
FimAlternaVelocidade
	BL   EsperaSoltar
	POP  {LR}
	BX   LR			
	
EsperaSoltar ; enquanto o botão estiver pressionado espera 100 ms
	PUSH {LR}
DelaySoltar
	MOV  R0, #100
	BL   SysTick_Wait1ms
	BL   PortJ_Input
	CMP	 R0, #2_00000011
	BNE  DelaySoltar
	POP  {LR}
	BX   LR			

; -------------------------------------------------------------------------------------------------------------------------
; Fim do Arquivo
; -------------------------------------------------------------------------------------------------------------------------	
    ALIGN                        ;Garante que o fim da se��o est� alinhada 
    END                          ;Fim do arquivo

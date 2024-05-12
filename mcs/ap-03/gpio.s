; gpio.s
; Desenvolvido para a placa EK-TM4C1294XL
; Prof. Guilherme Peron
; Ver 1 19/03/2018
; Ver 2 26/08/2018

; -------------------------------------------------------------------------------
        THUMB                        ; Instruções do tipo Thumb-2
; -------------------------------------------------------------------------------
; Declarações EQU - Defines
; ========================
; ========================
; Definições dos Registradores Gerais
SYSCTL_RCGCGPIO_R	 EQU	0x400FE608
SYSCTL_PRGPIO_R		 EQU    0x400FEA08
; ========================
; Definições dos Ports
; PORT J
GPIO_PORTJ_LOCK_R    	EQU    0x40060520
GPIO_PORTJ_CR_R      	EQU    0x40060524
GPIO_PORTJ_AMSEL_R   	EQU    0x40060528
GPIO_PORTJ_PCTL_R    	EQU    0x4006052C
GPIO_PORTJ_DIR_R     	EQU    0x40060400
GPIO_PORTJ_AFSEL_R   	EQU    0x40060420
GPIO_PORTJ_DEN_R     	EQU    0x4006051C
GPIO_PORTJ_PUR_R     	EQU    0x40060510	
GPIO_PORTJ_DATA_R    	EQU    0x400603FC
GPIO_PORTJ_IM_R     	EQU    0x40060410
GPIO_PORTJ_IS_R      	EQU    0x40060404
GPIO_PORTJ_IBE_R    	EQU    0x40060408
GPIO_PORTJ_IEV_R    	EQU    0x4006040C
GPIO_PORTJ_ICR_R    	EQU    0x4006041C
GPIO_PORTJ_RIS_R    	EQU    0x40060414
GPIO_PORTJ_MIS_R      	EQU    0x40060418
GPIO_PORTJ              EQU    2_000000100000000
	
; PORT N
GPIO_PORTN_LOCK_R    	EQU    0x40064520
GPIO_PORTN_CR_R      	EQU    0x40064524
GPIO_PORTN_AMSEL_R   	EQU    0x40064528
GPIO_PORTN_PCTL_R    	EQU    0x4006452C
GPIO_PORTN_DIR_R     	EQU    0x40064400
GPIO_PORTN_AFSEL_R   	EQU    0x40064420
GPIO_PORTN_DEN_R     	EQU    0x4006451C
GPIO_PORTN_PUR_R     	EQU    0x40064510	
GPIO_PORTN_DATA_R    	EQU    0x400643FC
GPIO_PORTN_DATA_BITS_R  EQU    0x40064000
GPIO_PORTN              EQU    2_001000000000000	
	
NVIC_EN1_R              EQU    0xE000E104
NVIC_PRI12_R            EQU    0xE000E430


; -------------------------------------------------------------------------------
; Área de Código - Tudo abaixo da diretiva a seguir será armazenado na memória de 
;                  código
        AREA    |.text|, CODE, READONLY, ALIGN=2

		; Se alguma função do arquivo for chamada em outro arquivo	
        EXPORT GPIO_Init            ; Permite chamar GPIO_Init de outro arquivo
		EXPORT PortN_Output			; Permite chamar PortN_Output de outro arquivo
		EXPORT GPIOPortJ_Handler						

;--------------------------------------------------------------------------------
; Função GPIO_Init
; Parâmetro de entrada: Não tem
; Parâmetro de saída: Não tem
GPIO_Init
;=====================
; 1. Ativar o clock para a porta setando o bit correspondente no registrador RCGCGPIO,
; após isso verificar no PRGPIO se a porta está pronta para uso.
; enable clock to GPIOF at clock gating register
            LDR     R0, =SYSCTL_RCGCGPIO_R  		;Carrega o endereço do registrador RCGCGPIO
			MOV		R1, #GPIO_PORTN                 ;Seta o bit da porta N
			ORR     R1, #GPIO_PORTJ					;Seta o bit da porta J, fazendo com OR
            STR     R1, [R0]						;Move para a memória os bits das portas no endereço do RCGCGPIO
 
            LDR     R0, =SYSCTL_PRGPIO_R			;Carrega o endereço do PRGPIO para esperar os GPIO ficarem prontos
EsperaGPIO  LDR     R1, [R0]						;Lê da memória o conteúdo do endereço do registrador
			MOV     R2, #GPIO_PORTN                 ;Seta o bit da porta N
			ORR     R2, #GPIO_PORTJ                 ;Seta o bit da porta J, fazendo com OR
            TST     R1, R2							;ANDS de R1 com R2
            BEQ     EsperaGPIO					    ;Se o flag Z=1, volta para o laço. Senão continua executando
 
; 2. Limpar o AMSEL para desabilitar a analógica
            MOV     R1, #0x00						;Colocar 0 no registrador para desabilitar a função analógica
            LDR     R0, =GPIO_PORTJ_AMSEL_R         ;Carrega o R0 com o endereço do AMSEL para a porta J
            STR     R1, [R0]						;Guarda no registrador AMSEL da porta J da memória
            LDR     R0, =GPIO_PORTN_AMSEL_R		    ;Carrega o R0 com o endereço do AMSEL para a porta N
            STR     R1, [R0]					    ;Guarda no registrador AMSEL da porta F da memória
 
; 3. Limpar PCTL para selecionar o GPIO
            MOV     R1, #0x00					    ;Colocar 0 no registrador para selecionar o modo GPIO
            LDR     R0, =GPIO_PORTJ_PCTL_R		    ;Carrega o R0 com o endereço do PCTL para a porta J
            STR     R1, [R0]                        ;Guarda no registrador PCTL da porta J da memória
            LDR     R0, =GPIO_PORTN_PCTL_R          ;Carrega o R0 com o endereço do PCTL para a porta N
            STR     R1, [R0]                        ;Guarda no registrador PCTL da porta F da memória
			
; 4. DIR para 0 se for entrada, 1 se for saída
            LDR     R0, =GPIO_PORTN_DIR_R		    ;Carrega o R0 com o endereço do DIR para a porta N
			MOV     R1, #2_0010					    ;PN1 & PN0 para LED
            STR     R1, [R0]						;Guarda no registrador
			LDR     R0, =GPIO_PORTJ_DIR_R		    ;Carrega o R0 com o endereço do DIR para a porta J
            MOV     R1, #0x00               		;Colocar 0 no registrador DIR para funcionar com entrada
            STR     R1, [R0]						;Guarda no registrador PCTL da porta J da memória
			
; 5. Limpar os bits AFSEL para 0 para selecionar GPIO 
;    Sem função alternativa
            MOV     R1, #0x00						;Colocar o valor 0 para não setar função alternativa
            LDR     R0, =GPIO_PORTN_AFSEL_R		    ;Carrega o endereço do AFSEL da porta N
            STR     R1, [R0]						;Escreve na porta
            LDR     R0, =GPIO_PORTJ_AFSEL_R         ;Carrega o endereço do AFSEL da porta J
            STR     R1, [R0]                        ;Escreve na porta
			
; 6. Setar os bits de DEN para habilitar I/O digital
            LDR     R0, =GPIO_PORTN_DEN_R		     	;Carrega o endereço do DEN
            MOV     R1, #2_00000010                     ;Ativa os pinos PN0 e PN1 como I/O Digital
            STR     R1, [R0]							;Escreve no registrador da memória funcionalidade digital 
 
            LDR     R0, =GPIO_PORTJ_DEN_R			    ;Carrega o endereço do DEN
			MOV     R1, #2_00000011                     ;Ativa os pinos PJ0 e PJ1 como I/O Digital      
            STR     R1, [R0]                            ;Escreve no registrador da memória funcionalidade digital
			
; 7. Para habilitar resistor de pull-up interno, setar PUR para 1
			LDR     R0, =GPIO_PORTJ_PUR_R			;Carrega o endereço do PUR para a porta J
			MOV     R1, #2_00000011						;Habilitar funcionalidade digital de resistor de pull-up 
                                                        ;nos bits 0 e 1
            STR     R1, [R0]							;Escreve no registrador da memória do resistor de pull-up
            
; Interrupção
; 1
			LDR     R0, =GPIO_PORTJ_IM_R
			MOV     R1, #2_00
			STR     R1, [R0]
; 2
			LDR     R0, =GPIO_PORTJ_IS_R
			MOV     R1, #2_00
			STR     R1, [R0]			
; 3.a)
			LDR     R0, =GPIO_PORTJ_IBE_R
			MOV     R1, #2_00
			STR     R1, [R0]			

; 3.b)
			LDR     R0, =GPIO_PORTJ_IEV_R
			MOV     R1, #2_10
			STR     R1, [R0]

; 4
			LDR     R0, =GPIO_PORTJ_ICR_R
			MOV     R1, #2_11
			STR     R1, [R0]

; 5
			LDR     R0, =GPIO_PORTJ_IM_R
			MOV     R1, #2_11
			STR     R1, [R0]
			
; 6.b)
			LDR     R0, =NVIC_EN1_R
			MOV     R1, #1
			LSL     R1, #19
			STR     R1, [R0]
			
; 7.b)
			LDR     R0, =NVIC_PRI12_R
			MOV     R1, #5
			LSL     R1, #29
			STR     R1, [R0]

;retorno            
			BX      LR

; -------------------------------------------------------------------------------
; Função PortN_Output
; Parâmetro de entrada: R0 --> se o BIT0 está ligado ou desligado
; Parâmetro de saída: Não tem
PortN_Output
	LDR	R1, =GPIO_PORTN_DATA_R		    ;Carrega o valor do offset do data register
	;Read-Modify-Write para escrita
	LDR R2, [R1]
	BIC R2, #2_00000011                     ;Primeiro limpamos os dois bits do lido da porta R2 = R2 & 11111100
	ORR R0, R0, R2                          ;Fazer o OR do lido pela porta com o parâmetro de entrada
	STR R0, [R1]                            ;Escreve na porta N o barramento de dados do pinos N0
	BX LR									;Retorno
	
GPIOPortJ_Handler
	LDR R0, =GPIO_PORTJ_RIS_R
	LDR R2, =GPIO_PORTJ_ICR_R
	LDR R1, [R0]
	AND R1, #2_11
	CMP R1, #2_10
	BEQ apagaLed
	CMP R1, #2_01
	BEQ acendeLed
	MOV R3, #2_11
	STR R3, [R2]
	BX  LR
apagaLed
	PUSH {LR}
	MOV R3, #2_10
	STR R3, [R2]
	MOV R0, #2_00
	BL  PortN_Output
	POP {LR}
	BX  LR	
acendeLed
	PUSH {LR}
	MOV R3, #2_01
	STR R3, [R2]
	MOV R0, #2_10
	BL  PortN_Output
	POP {LR}
	BX  LR	
	
	ALIGN
	END
;******************************************************************************
;
;                               STARTUP CODE
;                                 LM3Snnnn
;                             KEIL's uVision3 
;                   (RealView Microprocessor Developer Kit)
;
; Filename      : init.s
;******************************************************************************

                PRESERVE8
                AREA   INIT, CODE, READONLY                     ; Name this block of code                                   ;
                THUMB

;******************************************************************************
;                                  IMPORTS
;******************************************************************************
                                
                IMPORT  __main

;******************************************************************************
;                                  EXPORTS
;******************************************************************************

                EXPORT  ResetHndlr

;******************************************************************************
;                                DEFINITIONS
;******************************************************************************


;******************************************************************************
;                             PERFORM ROM/RAM REMAPPING
;******************************************************************************                

                ENTRY
ResetHndlr      

;******************************************************************************
;                              SETUP STACK POINTERS
;******************************************************************************
                

;******************************************************************************
;                                   MOVE TO MAIN
;******************************************************************************
                
				; STM32F4_M4 新增加, 有待验证是否正确
				IF {FPU} != "SoftVFP"
                                                ; Enable Floating Point Support at reset for FPU
                LDR.W   R0, =0xE000ED88         ; Load address of CPACR register
                LDR     R1, [R0]                ; Read value at CPACR
                ORR     R1,  R1, #(0xF <<20)    ; Set bits 20-23 to enable CP10 and CP11 coprocessors
                                                ; Write back the modified CPACR value
                STR     R1, [R0]                ; Wait for store to complete
                DSB
                
                                                ; Disable automatic FP register content
                                                ; Disable lazy context switch
                LDR.W   R0, =0xE000EF34         ; Load address to FPCCR register
                LDR     R1, [R0]
                AND     R1,  R1, #(0x3FFFFFFF)  ; Clear the LSPEN and ASPEN bits
                STR     R1, [R0]
                ISB                             ; Reset pipeline now the FPU is enabled
                ENDIF

				ldr     r0, =__main
                bx      r0                             	    ; Save this in register for possible long jump              ;

                ALIGN
                END 
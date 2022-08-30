        PUBLIC EightBitHistogram
        
        SECTION .text:CODE(2)
        
        THUMB
        
EightBitHistogram
        
        MUL     R0, R1                  ;R0 = R0 * R1
        
        CMP     R0, #65536              ;Compare image size with 64K
        ITT HS                          ;If image size is higher or same as 64K
        MOVHS   R0, #0                  ;R0 = 0
        BXHS    LR                      ;PC = LR

        MOV     R1, #0                  ;R1 = 0
        ADD     R12, R3, #512           ;R12 = [p_histogram + 512]
        
loop1   STR     R1, [R12, #-4]!         ;[R12] = 0
        CMP     R12, R3                 ;Compare [R12] with [p_histogram]
        BHI     loop1                   ;Branch to loop1 while [R12] > [p_histogram]
        
        ADD     R12, R2, R0             ;R12 = [R2 + R0]
        
        PUSH    {R0}                    ;Save R0 on the stack
        
loop2   LDRB    R1, [R12, #-1]!         ;R1 = [R12]
        LDRH    R0, [R3, R1, LSL #1]    ;R0 = [R3 + R1]
        ADD     R0, #1                  ;R0 = R0 + 1
        STRH    R0, [R3, R1, LSL #1]    ;[R3 + R1] = R0
        CMP     R12, R2                 ;Compare [R12] with [p_image]
        BHI     loop2                   ;Branch to loop2 while [R12] > [p_image]
        
        POP     {R0}                    ;Get R0 from the stack

        BX      LR                      ;PC = LR
        
        END
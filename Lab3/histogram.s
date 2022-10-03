        PUBLIC EightBitHistogram
        
        SECTION .text:CODE(2)
        
        THUMB
        
EightBitHistogram                       ; uint16_t width, uint16_t height, uint8_t const* p_image, uint16_t * p_histogram
                                        ; R0: uint16_t width
                                        ; R1: uint16_t height
                                        ; R2: uint8_t const* p_image
                                        ; R3: uint16_t* p_histogram
        
        MUL     R0, R1                  ; R0 = R0 * R1
                                        
        CMP     R0, #65536              ; Compare image size with 64K
        ITT HS                          ; If image size is higher or same as 64K
        MOVHS   R0, #0                  ; R0 = 0
        BXHS    LR                      ; PC = LR, return

        MOV     R1, #0                  ; R1 = 0, setter for reset histogram
        MOV     R12, #0                 ; R12 = 0, counter for reset histogram

reset_histogram   
        STR     R1, [R3, R12]           ; [R3+R12] = 0
        ADD     R12, R12, #4            ; R12 += 4 (no need to iterate with 
                                        ; halfword, because resetting a full 
                                        ; word resets 2 halfwords)
        CMP     R12, #512               ; Compare [R12] with 512, the total 
                                        ; size of p_histogram in bytes
        BNE     reset_histogram         ; Branch to reset_histogram 
                                        ; while R12 != 512

        MOV     R12, #0                 ; R12 is the counter from 0 to R0 (total size of image)
        PUSH    {R4}                    ; Push R4 to the stack

count_pixels   
        LDRB    R1, [R2, R12]           ; R1 = [R2 + R12], get image byte
        LDRH    R4, [R3, R1, LSL #1]    ; R4 = [R3 + R1], histogram position
        ADD     R4, #1                  ; R4 += 1
        STRH    R4, [R3, R1, LSL #1]    ; [R3 + R1] = R4
        ADD     R12, #1                 ; R12 += 1
        CMP     R12, R0                 ; Compare [R12] with image_size (R0)
        BNE     count_pixels            ; Branch to count_pixels while R12 != image_size
        
        POP     {R4}                    ; Get R4 from the stack

        BX      LR                      ; PC = LR, return
        
        END
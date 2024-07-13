; RAMSECTION locations are hardcoded inside LINKFILE

; Scratch RAM for general use 
; This is part of bank $7E and mirrored everywhere
.RAMSECTION "Zeropage" FORCE
    
    ZEROPAGE_END        DB
.ENDS

; Scratch and general RAM ONLY to be used during NMI
; This is part of bank $7E and mirrored everywhere
.RAMSECTION "NMI Page" FORCE
    
    NMI_RAM_END         DB
.ENDS

; HiRAM for general use
; This is part of bank $7E and mirrored everywhere
; 512 bytes allocated for stack space??
.RAMSECTION "HiRAM" FORCE
    
    HIRAM_END           DB
.ENDS

; The remaining $E000 bytes of LoRAM in bank 7E
.RAMSECTION "LoRAM 7E" FORCE

    LORAM_7E_END        DB
.ENDS

; The entire $10000 bytes of LoRAM in bank 7F
.RAMSECTION "LoRAM 7F" FORCE
    
    LORAM_7F_END        DB
.ENDS


; .IF ZEROPAGE_END >= $0100
;     .FAIL "Zeropage variables overflow alotted space!"
; .ENDIF
; 
; .IF NMI_RAM_END >= $0200
;     .FAIL "NMI variables overflow alotted space!"
; .ENDIF
; 
; .IF HIRAM_END >= $1D00
;     .FAIL "HiRAM overflows alotted space!"
; .ENDIF
; 
; .IF LORAM_7E_END > $FFFF
;     .FAIL "LoRAM (Bank 7E) overflows alotted space!"
; .ENDIF
; 
; .IF LORAM_7F_END > $FFFF
;     .FAIL "LoRAM (Bank 7F) overflows alotted space!"
; .ENDIF

.BANK $7E
.ORGA $0000
.RAMSECTION "HiRAM" FORCE
    
    HIRAM_END       DB
.ENDS


.BANK $7E
.ORGA $1D00
.RAMSECTION "HiRAM" FORCE
    
    NMI_RAM_END       DB
.ENDS


.BANK $7E
.ORGA $2000
.RAMSECTION "LoRAM 7E" FORCE

    LORAM_7E_END    DB
.ENDS


.BANK $7F
.ORGA $0000
.RAMSECTION "LoRAM 7F" FORCE
    
    LORAM_7F_END    DB
.ENDS


.IF HIRAM_END >= $1D00
    .FAIL "HiRAM overflows alotted space!"
.ENDIF

.IF NMI_RAM_END >= $1E00
    .FAIL "NMI variables overflow alotted space!"
.ENDIF

.IF LORAM_7E_END > $FFFF
    .FAIL "LoRAM (Bank 7E) overflows alotted space!"
.ENDIF

.IF LORAM_7F_END > $FFFF
    .FAIL "LoRAM (Bank 7F) overflows alotted space!"
.ENDIF

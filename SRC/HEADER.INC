;------------------------------ HEADER FILE --------------------------------;
; This header file has been adapted from others found on superfamicom.org.  ;
; This definition has been altered to support a HiROM mapping, instead of   ;
; LoROM.                                                                    ;      
;---------------------------------------------------------------------------;

; == HiROM Memory Layout ==

.BASE $C0

BANKNO = 2
.ROMBANKMAP
    BANKSTOTAL  BANKNO + 2  ; Two dummy banks for WRAM
    BANKSIZE    $10000      ; Banks are 65K
    BANKS       BANKNO + 2
.ENDRO

.MEMORYMAP
    SLOTSIZE    $10000
    DEFAULTSLOT 0
    SLOT        0 $0000
.ENDME

.BANK 0
.BASE 0
.SNESHEADER
    ID "SNES"                       ; Unknown identification string (4 chars)
    ;              111111111122
    ;     123456789012345678901
    NAME "  VERY NICE TEST :D  "    ; “Game” name, must be 21 chars 
    
    FASTROM                         ; We go fastttttt (3.58 MHz Babyyy)
    HIROM

    CARTRIDGETYPE $00               ; Literally just ROM
    ROMSIZE       $07               ; Log2 of size of ROM in KB (128KB = 7, 256KB = 8, etc.) 
    SRAMSIZE      $00               ; No SRAM
    COUNTRY       $07               ; Belgium and the Netherlands
    LICENSEECODE  $00               ; 0 because we're not officially licensed, teehee
    VERSION       $00               ; High nibble is the major version number, low nibble is the minor version number
.ENDSNES

; Interrupt Vector Definitions
.SNESNATIVEVECTOR                   ; Native mode vectors
    COP         EmptyHandler
    BRK         EmptyHandler
    ABORT       EmptyHandler
    NMI         EmptyHandler
    IRQ         EmptyHandler
.ENDNATIVEVECTOR

.SNESEMUVECTOR                      ; Mostly unnecessary, emulation mode is not used besides during boot
    COP         EmptyHandler
    ABORT       EmptyHandler
    NMI         EmptyHandler
    RESET       BootHandler         ; SNES Boots in Emulation mode, this is the entrypoint to the code
    IRQBRK      EmptyHandler
.ENDEMUVECTOR

.INCLUDE "SRC/LINKTREE.INC"

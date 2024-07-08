;------------------------------ HEADER FILE --------------------------------;
; Dit headerbestand is een versie van anderen gevonden op superfamicom.org. ;
; Deze header is aangepast om HiROM mapping te ondersteunen, in plaats van  ;
; een LoROM mapping.                                                        ;
;---------------------------------------------------------------------------;

.INCLUDE "INCLUDES.INC"

.DEF BANKNO 2               ; I don't know how to properly link files
                            ; So everything's gonna global

; == HiROM Memory Layout ==
.ROMBANKMAP
    BANKSTOTAL BANKNO + 2   ; Insert two virtual memory banks
    BANKSIZE $10000         ; Banks are 65K
    BANKS BANKNO + 2
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


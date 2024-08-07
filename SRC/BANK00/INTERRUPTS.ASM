.BANK $00
.ORG $8000
.SECTION "Boothandler" SEMIFREE
; The first code the processor runs when booting up
; (This code exists both on Bank 00 and C0)
BootHandler:
    LDA.B #$04              ; Turns OFF: Emulation mode, Decimal mode
    PHA                     ; Turns ON:  Interrupt disable
    PLP
    XCE                     ; Switch to native mode

    REP.B #$10              ; X large
    LDX.W #$1FFF
    TXS                     ; Point stack to highest address of HiRAM
    PEA.W $0000
    PLD                     ; Point Direct Page register to Page 0 to be sure

    LDA.B #$01
    STA.W MEMSEL            ; Tell the system that we intend on going fast
    JML   _clear_PPU        ; (Dummy) jump to the upper banks for that speed

_clear_PPU:
    REP.B #$20              ; A large
    SEP.B #$10              ; X smoll

; Init page $2100 registers
    LDA.W #$2100
    TCD                     ; $2100 to DP

    LDA.W #$008F
    STA.B $00               ; $2100 & $2101

    LDX.B #($0B - $01)      ; Clear from $210C to $2102, writing 2 bytes at a time
-:  STZ.B $01, X
    DEX
    DEX
    BPL   -

    SEP.B #$30              ; A & X small
    LDX.B #($14 - $0D)
-:
    STZ.B $0D, X
    STZ.B $0D, X
    DEX
    BPL   -

    STZ.B $1C
    STZ.B $1C
    STZ.B $1D
    STZ.B $1D
    STZ.B $1F
    STZ.B $1F
    STZ.B $20
    STZ.B $20

    REP.B #$20              ; A large
    LDX.B #($2E - $23)
-:
    STZ.B $23, X
    DEX
    DEX
    BPL   -

    SEP.B #$30              ; A & X small
    STZ.B $1A
    STZ.B $21
    STZ.B $31
    STZ.B $33

    LDA.B #$80              ; Whatever I couldn't fit into neat logic
    STA.B $15
    LDA.B #$01
    STZ.B $1B
    STA.B $1B
    STZ.B $1E
    STA.B $1E
    LDA.B #$30
    STA.B $30
    LDA.B #$E0
    STA.B $32

; Init page $4200 registers
    REP.B #$20              ; A large
    LDA.W #$4200
    TCD

    LDX.B #($0D - $02)
-:
    STZ.B $02, X
    DEX
    DEX
    BPL   -
    
    SEP.B #$30
    STZ.B $00
    LDA.B #$FF
    STA.B $01

    PEA.W $0000
    PLD                     ; Reset the Direct Page Register
    JMP.W Main
.ENDS

.BANK $00
.ORGA $8000
.SECTION "EmptyHandler" SEMIFREE
; This can only have been triggered unintentionally
; Perhaps I could add in some fancy crash screen if I feel like it later
EmptyHandler:
    STP                     ; Just fucking die
.ENDS

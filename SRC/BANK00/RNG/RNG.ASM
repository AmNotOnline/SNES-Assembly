.ORGA $8000
.SECTION "GetRNG" SEMIFREE
; Expects A8
; A8 contains the new Random Number
GetRNG:
    LDA.W STAT78    ; Reset latch flip-flops
    LDA.W SLVH      ; Latch scan beam position
    LDA.W OPVCT     ; Read vertical position
    EOR.B #$FF
    EOR.W OPHCT     ; Read horizontal position (Ranges from 0 to 339)

    RTL

.ENDS

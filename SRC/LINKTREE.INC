
; Ram layout
.INCLUDE "SRC/RAM.INC"

; General definitions and documentation, like registers and memory locations
.INCLUDE "SRC/INCLUDES.INC"

.BASE $C0
; Interrupts and their handlers
; Also does init (emulation mode RST signal handler)
.INCLUDE "SRC/BANK00/INTERRUPTS.ASM"

; Main code file
.INCLUDE "SRC/BANK00/MAIN.ASM"

PPU:
	INIDISP = $2100	; Screen brightness + F-blank
;					; Contents: F000 BBBB
;					;           ¦    +---> Screen brightness: $0:darkest, $F:brightest (normal game level)
;					;			+> Force blanking: 1:F-Blank active, 0:F-blank non-active
;
	OBJSEL = $2101	; = OAM Size: Denotes size of sprites & location of OAM in VRAM
;					; Contents: SSSP PBBB
;					;			¦¦¦¦ ¦+--> OAM Base address (upper 3 bits): Sets OAM at $0000, $2000, $4000 or $6000
;					;			¦¦¦¦ ¦	   ¦ Upper bit is always 0,					   (%000),(%001),(%010) or(%011)
;					;		   	¦¦¦¦ ¦	   + as VRAM was never expanded to 128K (64K Word)
;					;			¦¦¦+--> Adds offset for upper page of OAM to lower page of OAM (BBB), P0+$1000(Normal, no gap),
;					;			¦¦¦		¦ P0+$2000(%01), P0+$3000(%10),P0+$4000(%11) The base address of Page 1 wraps around at
;					;			¦¦¦		+ $8000 (P0 can be at $6000 (%011) with P1 at $2000 (%11))
;					;			+--> Object sizes: Denote which sizes objects (sprites) can use:
;					;				 %000	: S:8x8		L:16x16		(S = small)
;					;				 %001	: S:8x8		L:32x32		(L = large)
;					;				 %010	: S:8x8		L:64x64		(Size is encoded along with an object's data)
;					;				 %011 	: S:16x16	L:32x32		(in its OAM entry)
;					;				 %100	: S:16x16	L:64x64
;					;				 %101	: S:32x32   L:64x64
;					;				 %110	: S:16x32   L:32x64 -> These aren't meant to be used and behave weirdly
;					;				 %111   : S:16x32   L:32x32 +  with mirroring
;
	OAMADDL = $2102	; OAM access, for both address to read / write to and priority rotation (2 bytes)
	OAMADDH = $2103	; Contents: P000 000a($03) aAAA AAAA($02)
;					;			¦       ¦      ¦¦++-++++> [AAA AAAA] OAM object index to make max priority with P ($00 - $7F)
;					;			+-------+------++++-++++> [P] Initialize object priority for [AAA AAAA] (Make max priority?)
;					;					+---------------> [a aAAA AAAA] OAM address to read / write to (coupled with $04 & $38)
;
	OAMDATAW = $2104; For writing to the OAM word-index specified by OAMADDL & OAMADDH, write twice: low, high
;
	BGMODE = $2105	; Sets the Background mode, BG3 priority on Mode 1, and denotes character size (NOT OBJECT SIZE!!)
;					; Contents: 4321 PMMM
;					;			¦¦¦¦ ¦+--> Sets the background mode (%000:Mode 0, %001:Mode 1 etc.)
;					;			¦¦¦¦ +> This makes BG3 high priority in BG Mode 1 (useful for HUDs)
;					;			+---> Sets the size of tiles in BG modes 0 through 6, for the BG number above
;					;				  %0	: 8x8 in modes 0-4, 16x8 in 5&6 to appear square
;					;				  %1	: 16x16 in all BG modes, vert. stretched in modes 5&6
;					;				   Large characters will add +$01 to find their horizontal neighbour, +$10 for their
;					;				   vertical neighbour, and +$11 for the fourth tile in the character
;					;				   Characters are always 8x8 in mode
;
	BG1SC	= $2107	; Controls where in VRAM the BG layout data is stored + how large each background is
	BG2SC	= $2108	; Contents: AAAA AASS
	BG3SC	= $2109	;			¦¦¦¦ ¦¦+-> Controls the size of the background, 1 screen, 2 v. stacked, 2 h. stacked, or 4 screens
	BG4SC	= $210A	;			¦¦¦¦ ¦¦	   Each chunk of 32x32 tiles is $400 bytes, a 64x64 background will total $1000 bytes
;					;			¦¦¦¦ ¦¦    All 32x32 chunks are stored right after one another
;					;			+------> Denotes the location of the background's layout data location (in steps of $400)
;
	BG12NBA	= $210B	; Controls where in VRAM the graphics data for each background is stored	
	BG34NBA = $210C	; Contents: AAAA BBBB
;					;			¦¦¦¦ +---> Controls where in VRAM the graphics data for the lower BG is stored in steps of
;					;			¦¦¦¦	   $1000 bytes
;					;			+---> Same, but for the high BG of the pair
;					;				Max length of one is $3FF tiles ($3FF0 bytes in 2bpp, $5FE8, in 3bpp, $7FE0 in 4bpp)
;					;				Maybe it's wise to reuse tiles
;
	BG1HOFS = $210D	; Contains the horizontal scrolling information for BG 1
;					; 10 bits in BGModes 0-6 (0~1023), 13 bits in BGmode 7 (-4096~4096)
;					; Write twice: low, high(2/5 bits)
;
	BG1VOFS = $210E	; Contains the vertical scrolling information for BG 1
;					; Same explanation as above
;
	BG2HOFS = $210F   ; Same behavior as above, only without scrolling for BGMode 7, write twice low, high
	BG2VOFS = $2110
	BG3HOFS = $2111
	BG3VOFS = $2112
	BG4HOFS = $2113
	BG4VOFS = $2114

;
;
	VMAINC = $2115	; Contains the auto-incrementing behavior for VRAM access
;					; Contents: H000 RRII
;					;			¦    ¦¦+-> Sets the increment amount (Useful for updating tilemaps)
;					;			¦	 ¦¦	   %00: + 1 Updates background in a horizontal manner
;					;			¦	 ¦¦	   %01: +32 Updates background in a vertical manner (mode 0-6)
;					;			¦	 ¦¦	   %1-: +128Updates background in a vertical manner (mode 7)
;					;			¦	 +-> Remaps VRAM addressing to allow character data to be fed in rows of pixels, instead
;					;			¦		 of doing it tile-by-tile, to compress better
;					;			¦		 %00: No remapping
;					;			¦		 %01: YYYYYYYYRRRXXXXX -> YYYYYYYYXXXXXRRR (256px(32tiles) of 2bpp data at a time)
;					;			¦			:									   (128px(16tiles) of 4bpp data)
;					;			¦			:									   (64 px(8 tiles) of 8bpp data)
;					;			¦		 %10: YYYYYYYRRRXXXXXX -> YYYYYYYXXXXXXRRR (Double the above)
;					;			¦		 %11: YYYYYYRRRXXXXXXX -> YYYYYYXXXXXXXRRR (Quadruple that of %01)
;					;			+> Decides when to auto-increment $16 & $17 (%1 is default)
;					;			   %0: After $18 or $39: Allows for reading or writing only the low bytes in word addresses
;					;			   %1: After $19 or $3A: Allows for reading or writing only the high bytes in word addresses
;
	VMADDL = $2116	; Used to select a 15-bit word address in VRAM
	VMADDH = $2117	; Auto incrementing behavior is selected with $15
;
	VMDATAL = $2118	; 16-bit data to be written to the address in $16 & $17
	VMDATAH = $2119
;
    M7SEL = $211A   ; Initial settings for BGMode 7
;                   ; Contains: SS00 00VH
;                   ;           ||     ++> Vertical and Horizontal flipping of background
;                   ;           ++-------> %00: Screen repetition if outside screen area
;                   ;                      %10: Outside is fallback color
;                   ;                      %11: Character #00 gets repeated outside of screen area
;
    M7A = $211B     ; Matrix parameters for the BGMode 7 background
    M7B = $211C     ; Check docs for more info
    M7C = $211D     ; Write twice
    M7D = $211E
    M7X = $211F
    M7Y = $2120
;
	CGADD = $2121		; CGRAM address to read / write to, selects the color cell ($00-$FF)
;
	CGDATAW = $2122	; Color data to write to the cell selected with $21, write twice: low, high
;
    W12SEL = $2123  ; Contains info on which layers the windows should be enabled. and whether these are inverted 
    W34SEL = $2124  ; Contains: ABCD EFGH
    WOBJSEL= $2125  ;           |||| |||+> Invert window 1 toggle: 0: normal, 1: inverted
;                   ;           |||| ||+-> Window 1 enable on layer one
;                   ;           |||| ++> Same as two rows above, but for window 2
;                   ;           ++++-> Same as three rows above, but for layer two
;                   ;                  For WOBJSEL: Upper nibble is Color Window, lower nibble is Object layer
;
    WH0 = $2126     ; Window 1 left position
    WH1 = $2127     ;  --//--  right position
    WH2 = $2128     ; Window 2 left position
    WH3 = $2129     ;  --//--  right position
;
    WBGLOG = $212A  ; Mask logic settings for windows 1 and 2
    WOBJLOG= $212B  ; Contains: AABB CCDD
;                   ;                  ++>:%00: OR
;                   ;                      %01: AND
;                   ;                      %10: XOR
;                   ;                      %11: XNOR
;                   ; These are grouped going BG4 to 1. high to low
;                   ; On WOBJLOG, only the lower nibble is used, with Color layer, and objects respectively occupying the slot
;
	TM      = $212C	; Designates layers to the main screen
	TS		= $212D	; Designates layers to the sub screen (to be added to / subtracted from main)
;
    CGSWSEL = $2130 ; Initial settings for fixed color addition or screen addition 
;                   ; Contains: MMSS 00AD
;                   ;           ||||   |+> Direct select: the VRAM data becomes the color data itself
;                   ;           ||||   |   +Only available in BGModes 3, 4, & 7
;                   ;           ||||   +> Fixed color addition / subtraction toggle
;                   ;           ||||      |0: Math with Main Screen and Fixed color
;                   ;           ||||      +1: Math with Main- and Sub-Screen
;                   ;           ++++> Color window On/Off to Main/Sub switch
;                   ;                 |%00: Always on
;                   ;                 |%01: Only on inside of window
;                   ;                 |%10: Only on outside of window
;                   ;                 |%11: Always off
;                   ;                 +MM is for main screen, SS is for sub screen
;
    CGADSUB = $2131 ; Addition/ subtraction designation for each screen
;                   ; Contains: CHFS 4321
;                   ;           ||++-++++> Color data math enable: designate BG1~4, Objects, and fallback color
;                   ;           ||         :for color math with the sub screen or fixed color
;                   ;           ||         +NOTE: for Objects, this only works when they have pallette 4~7
;                   ;           |+-----> Half color enable switch, AKA, take the average of the color maths for semi-transparency
;                   ;           +----> Color data addition/ subtraction switch 
;                   ;                  +When using math between the screen, either can be used, as this has no effect without the color screen
;
    COLDATA = $2132 ; Fixed color data
;                   ; Contains: BGR4 3210
;                   ;           |||+-++++> Color data 
;                   ;           +++----> Toggle for each color, multiple can be set at once for grays and blends
;
	SLHV    = $2137     ; Software latch for the H and V position of the scanning beam, reading latches the data
;					    ; When latched, data can be read from OPHCT & OPVCT, SLHV always contains garbage data
;
	OAMDATAR = $2138	; For reading from the OAM-index specified by OAMADDL & OAMADDH, read twice: low, high
;
	VMDATALR = $2139	; Reads the current value of the bytes in VRAM at the location of VMADDH & VMADDL 
	VMDATAHR = $213A	; Originally also called VMDATAL & VMDATAH, but have an R appended here to signify that they're only for reading data
;
	CGDATAR = $213B	; To read from the color cell selected with $21, read twice: low, high
;
	OPHCT = $213C		; Hor position of the scanner beam when last latched via $37
	OPVCT = $213D		; Ver
;
  AUDIO_0 = $2140  ; APU ports
  AUDIO_1 = $2141
  AUDIO_2 = $2142
  AUDIO_3 = $2143
;
	STAT77	= $213E 	; CPU version number + some flags !!RESETS NMI FLAG AFTER READING!!
;
	WMDATA = $2180	; To both read or write to an address in WRAM, selected with $81-$83 (Mostly used with (H)DMA)
;
	WMADDL = $2181	; To select a byte in WRAM to access with register $80, WMADDL & WMADDM work as expected to access the
	WMADDM = $2182	; address, but only the lowest bit of WMADDH needs to be written to to select bank $7E (%0) or bank $7F (%1)
	WMADDH = $2183	; The address automatically increments

CPU:
	NMITIMEN = $4200	; Bit 7: NMI enable, Bits 5&4: IRQ enable, V&H; Bit 0: STD Joypad read enable
;
	WRMPYA = $4202 	; Unsigned 8-bit multiplication registers
	WRMPYB = $4203  ; Starts when B is set and takes 8 machine cycles to complete
;
    WRDIVL = $4204  ; Dividend for hardware division
    WRDIVH = $4205  ;
;
    WRDIVB = $4206  ; Divisor for hardware division, division starts as soon as B is set, and takes 16 cycles
;
    HTIMEL = $4207  ; Horizontal location of when the timed hardware interrupt should occur
    HTIMEH = $4208  ; This is enabled through register $4200
;
    VTIMEL = $4209  ; Vertical location of hardware IRQ interrupt, see above
    VTIMEH = $420A  ;   
;
	MDMAEN = $420B	; The trigger for any standard DMA channel to start execution, will suspend the CPU for the duration
					; Bits get turned off when execution is complete
;
	HDMAEN = $420C	; Trigger for HDMA channel standby mode, does not get turned off automatically
;
    MEMSEL = $420D  ; Bit 0 triggers FastROM in upper half of memory
;
	RDNMI  = $4210	; CPU version number + !!RESETS NMI FLAG!!
;
	HVBJOY = $4212	; 7th bit: currently in V-blank?, 6th bit: currently in H-blank?, 0th bit: currently reading controller data?
;
	CTRL1L = $4218	; [A, X, L, R, 0, 0, 0, 0] Controller data shifted in from STD joypad read
	CTRL1H = $4219	; [B, Y, s, S, u, d, l, r]
	CTRL2L = $421A
	CTRL2H = $421B
	CTRL3L = $421C
	CTRL3H = $421D
	CTRL4L = $421E
	CTRL4H = $421F

General:
	Asmall = $20
	Xsmall = $10

    Button_A = $80
	Button_X = $40
	Button_L = $20
	Button_R = $10
    ;$4219
	Button_B = $80
	Button_Y = $40
	Button_Select = $20
	Button_Start  = $10
	Button_Up 	  = $08
	Button_Down	  = $04
	Button_Left   = $02
	Button_Right  = $01


;Interrupt access macros
.MACRO EI
    CLI
.ENDM

.MACRO DI
    SEI 
.ENDM

.MACRO WDM ARGS OPERAND             ; WDM undefined in WLA-65816?
    .DB $42, OPERAND
.ENDM

.STRUCT OAM_LO_ENTRY
    XPos DB
    YPos DB
    Imag DB
    Flag DB
.ENDST

.STRUCT OAM_HI_ENTRY
    Flag DB
.ENDST


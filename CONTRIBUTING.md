# Contributing

## Style Guide

### General Guidelines

- It is encouraged to make lines no longer than 96 characters, but this is a an encouragment
rather than a rule.
- Multiples of 4 spaces should be used for indentation for code.
- Statements are usually after the first tab, but more indentation can be used for loops.
- Global labels should be at the very beginning of the line, and and with a colon.
- Compiler directives should be in all caps and at the very beginning of a line (a tab can be
used in case of blocks of directives, like with `.MEMORYMAP`).
- Comments begin with "`; `" (semicolon and space), and have consistent outlining.

### Naming Guidelines

Variables should be names in `camelCase` with Reverse Hungarian Notation.  

**General Variables**: The datatype part of the variable name uses `u` or `i` to denote whether
it is signed or unsigned, followed by the number of bits. For example, `charIndex_u8` would be 
an unsigned 8-bit integer. All signed integers should be in two's complement unless explicitly 
specified otherwise.  

When **fixed point numbers** are used, the number of bits gets represented as 
`{whole}p{fraction}`. As an example, `vSpeed_i4p4` would be a signed 4.4 fixed point number,
using 4 bits for the integer portion of the number, and 4 bits for the fractional part.
*Whether a signed fixed point number uses one's or two's complement should be made clear, and
is not represented in this notation. Both can be used, and there is no preferred option.*  

The datatype of **arrays** are notated in the same way as variables, with `A` appended to the
end. For good housekeeping, it is incouraged to add a label after the array that denotes the
byte after the end of the array, notated with ending on `AE` instead of just `A`. A good array
definition could go as follows:

```assembly
enemyHealth_u16A:                             ; This definition is technically not correct,
    .DW 30, 45, 100, 60, 80, 90, 150          ; as it should be a constant, but it serves as
enemyHealth_u16AE:                            ; a decent example.
```

**Pointers** are notated as the datatype they point to, followed by `P` for 16-bit pointers, or 
`Q` for 24-bit pointers. When using 16-bit pointers, comments around the definition should 
make it clear which bank the pointer expects to be extended with. `actorHP_u16Q` would be a
pointer to an unsigned 16-bit integer that stores the 24-bit address of the data it references.  

**Other datatypes**:

- `bool` is used for booleans;
- `char` is used to denote a character;
- `str` for a string (being a neater shorthand for `cA`) and uses `sE` as its ending signature[^1];
- Other custom datatypes can be defined as needed, but should be documented and communicated
clearly. One-off datatypes that aren't concretely defined and used multiple times in the code 
base (like some sort of tuple in a normal programming language) should be defined as
`X{# bytes}`. In this case, what this complex data structure is, how it is made, and where it
should be stored etc. should be documented in comments.

When combining multiple suffixes, the most relevant one should be at the back. For example, a
16-bit pointer to an array of 24-bit pointers to unsigned 8-bit integers would be named 
`dataPointer_u8QAP`. To avoid confusion, underscores can be used to separate the different 
parts of the name.

[^1]: Strings don't need to be null-terminated, nor have they to be encoded in ASCII. If the 
usage and encoding is clear enough, the datatype can be `str`.

---

### Constants

Constants may be compiler directives, constants in ROM or RAM, or other values that are not
expected to change like lookup tables. Constants should be named in `UPPER_SNAKE_CASE`, using
reverse Hungarian Notation as described under Variables above.

Bringing all of the above together, a complicated example could be:

```assembly
SPRITE_OFFSET_H_i7p8AP                        ; A 16-bit pointer to an array of signed 
                                              ; 7.8 fixed point numbers (with implied sign bit)
```

---

### Labels / Functions

Labels and functions represent blocks of code that can be called or otherwise jumped to to be
executed. These can be code in ROM, or self-modifying code in RAM.

#### Global

Global Labels / Functions should be named in `PascalCase`. The following should be documented
in comments above the label:

- Name and Description, longer version of the name if applicable
- Inputs
- Outputs
- Which registers are altered
- Flags that are altered (if applicable)

Whenever possible, functions should be self-contained and reside inside of their own `.SECTION`
block to insure that code is weaved together efficiently (and unused functions get left out).

#### Local

Local labels / functions are to be used within another function, and therefore are not expected
to be documented so thoroughly – what the writer deems necessary should be documented. Local
labels / functions should be named in `snake_case`, beginning with a "`_`".

---

### Registers

Registers are named exactly as they are on [FullSNES](https://problemkaputt.de/fullsnes.htm#snesiomap).

---

### Examples

```assembly
charIndex_u8                ; unsigned 8-bit integer
vSpeed_i4p4                 ; signed 4.4 fixed point number

enemyHealth_u16A            ; array of unsigned 16-bit integers
    .DB ...                 ; (data)
enemyHealth_u16AE           ; end of array

actorHP_u16Q                ; 24-bit pointer to unsigned 16-bit integer

choiceSlot_char             ; character
npcDialogueEntry_str        ; string
spritePosition_X4           ; 4-byte custom datatype (2x u8p8 for example)

SPRITE_OFFSET_H_i7p8AP      ; 16-bit pointer to array of signed 7.8 fixed point numbers

; ============================================================================================= ;
; CopyToStack                                                                                   ;
;   Copies x amount of bytes pointed to to the stack, moving the stack pointer accordingly.     ;
; ============================================================================================= ;
; Inputs:                                                                                       ;
;   A16: Number of bytes to copy - 1                                                            ;
;   X16: Pointer to the last byte of data to copy                                               ;
;   Y16: Contains the source bank in the lower byte, and $5C in the upper byte                  ;
; Outputs:                                                                                      ;
;   None                                                                                        ;
; Altered Registers:                                                                            ;
;   All                                                                                         ;
CopyToStack:                ; Global label
    ...
_loop:                      ; Local label
    ...
    DEX
    BEQ _loop               ; Use of local label

    LDA.W WOBJSEL           ; Loading register $2125 into the Accumulator
```

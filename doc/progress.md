# Progress

## Aim
This document aims to present progress on implementing the ISA, differentiating between implementation at a decoder level and executable level.
The distinction appears due to how the fetch-decode-execute cycle is implemented in this simulator. Unlike in a real processor, instructions are prefetched, read from disk into the emulator's RAM before execution. Beyond faster access, there is no benefit from this, but it was chosen an interim sollution. Perhaps future versions will implement real ISA behavior

This will be a long project. Very likely testing will take even longer. So don't expect the Christmas tree to light up fully green anytime soon. Ideally, once a _preliminary_ implementation is done, I'll write some unittests to make sure instructions are read and do what they're supposed to. Till then, it's the wild, wild west out here!

## Progress table

:x: =                      Not implemented

:construction: =            Partial implementation available

:warning: = Implemented, but untested / partially tested

:white_check_mark: =       Fully implemented

Note: for ranges marked with `->`, they follow an easy enough pattern that can be implemented in such a way that they're treated as one case. ( at least, this is what I believe now, at the start of the project. If it turns out to need multiple cases, I will update the list accordingly )
This brings me on a tangent: I am aware that even instructions with the same name but a different prefix can be done in such a way that they take up only one case. This is a planned future development. Because internally the interpreter uses switch statements, minimizing the number of cases _should_ somewhat increase performance.

Note 2: If it seems that opcodes are implemented at random, that's because they truly are. In the first phase, trying to see if the project is fesable, I took a random program which adds two numbers, a and b, compiled to .hex and started by implementing only the instructions available in it.


|         OPCODE        |          DECODABLE        |     EXECUTABLE     |
|:---------------------:|:-------------------------:|:------------------:|
| 00xx, NOP             |         :warning:         |      :warning:     |
| 01xx, MOVW            |         :warning:         |      :warning:     |
| 02xx, MULS            |         :warning:         |      :warning:     |
| 03xx, MULSU           |         :warning:         |      :warning:     |
| 03xx, FMUL            |         :warning:         |      :warning:     |
| 03xx, FMULS           |         :warning:         |         :x:        |
| 03xx, FMULSU          |         :warning:         |         :x:        |
| 04xx, CPC             |         :warning:         |         :x:        |
| 05xx, CPC             |         :warning:         |         :x:        |
| 06xx, CPC             |         :warning:         |         :x:        |
| 07xx, CPC             |         :warning:         |         :x:        |
| 08xx, SBC             |         :warning:         |         :x:        |
| 09xx, SBC             |         :warning:         |         :x:        |
| 0Axx, SBC             |         :warning:         |         :x:        |
| 0Bxx, SBC             |         :warning:         |         :x:        |
| 0Cxx, ADD             |         :warning:         |      :warning:     |
| 0Dxx, ADD             |         :warning:         |      :warning:     |
| 0Exx, ADD             |         :warning:         |      :warning:     |
| 0Fxx, ADD             |         :warning:         |      :warning:     |
| 10xx, CPSE            |         :warning:         |         :x:        |
| 11xx, CPSE            |         :warning:         |         :x:        |
| 12xx, CPSE            |         :warning:         |         :x:        |
| 13xx, CPSE            |         :warning:         |         :x:        |
| 14xx, CP              |         :warning:         |         :x:        |
| 15xx, CP              |         :warning:         |         :x:        |
| 16xx, CP              |         :warning:         |         :x:        |
| 17xx, CP              |         :warning:         |         :x:        |
| 18xx, SUB             |         :warning:         |         :x:        |
| 19xx, SUB             |         :warning:         |         :x:        |
| 1Axx, SUB             |         :warning:         |         :x:        |
| 1Bxx, SUB             |         :warning:         |         :x:        |
| 1Cxx, ADC             |         :warning:         |         :x:        |
| 1Dxx, ADC             |         :warning:         |         :x:        |
| 1Exx, ADC             |         :warning:         |         :x:        |
| 1Fxx, ADC             |         :warning:         |         :x:        |
| 20xx, AND             |         :warning:         |         :x:        |
| 21xx, AND             |         :warning:         |         :x:        |
| 22xx, AND             |         :warning:         |         :x:        |
| 23xx, AND             |         :warning:         |         :x:        |
| 24xx, EOR             |         :warning:         |         :x:        |
| 25xx, EOR             |         :warning:         |         :x:        |
| 26xx, EOR             |         :warning:         |         :x:        |
| 27xx, EOR             |         :warning:         |         :x:        |
| 28xx, OR              |         :warning:         |         :x:        |
| 29xx, OR              |         :warning:         |         :x:        |
| 2Axx, OR              |         :warning:         |         :x:        |
| 2Bxx, OR              |         :warning:         |         :x:        |
| 2Cxx, MOV             |         :warning:         |      :warning:     |
| 2Dxx, MOV             |         :warning:         |      :warning:     |
| 2Exx, MOV             |         :warning:         |      :warning:     |
| 2Fxx, MOV             |         :warning:         |      :warning:     |
| 30xx -> 3Fxx, CPI     |         :warning:         |         :x:        |
| 40xx -> 4Fxx, SBCI    |         :warning:         |         :x:        |
| 50xx -> 5Fxx, SUBI    |         :warning:         |         :x:        |
| 60xx -> 6Fxx, ORI     |         :warning:         |         :x:        |
| 70xx -> 7Fxx, ANDI    |         :warning:         |         :x:        |
| 80xx, LD              |         :warning:         |         :x:        |
| 80xx, LDD             |         :warning:         |      :warning:     |
| 81xx, LD              |         :warning:         |         :x:        |
| 81xx, LDD             |         :warning:         |      :warning:     |
| 82xx, ST              |         :warning:         |         :x:        |
| 82xx, STD             |         :warning:         |      :warning:     |
| 83xx, ST              |         :warning:         |         :x:        |
| 83xx, STD             |         :warning:         |      :warning:     |
| 84xx, LDD             |         :warning:         |      :warning:     |
| 85xx, LDD             |         :warning:         |     :warning:     |
| 86xx, STD             |         :warning:         |      :warning:     |
| 87xx, STD             |         :warning:         |      :warning:     |
| 88xx, LDD             |         :warning:         |      :warning:     |
| 89xx, LDD             |         :warning:         |      :warning:     |
| 8Axx, STD             |         :warning:         |      :warning:     |
| 8Bxx, STD             |         :warning:         |      :warning:     |
| 8Cxx, LDD             |         :warning:         |      :warning:     |
| 8Dxx, LDD             |         :warning:         |      :warning:     |
| 8Exx, STD             |         :warning:         |      :warning:     |
| 8Fxx, STD             |         :warning:         |      :warning:     |
| 90xx, LDS             |            :x:            |         :x:        |        
| 90xx, LD              |            :x:            |         :x:        |
| 90xx, POP             |         :warning:         |      :warning:     |
| 90xx, LDS             |            :x:            |         :x:        |
| 90xx, LD              |            :x:            |         :x:        |
| 90xx, POP             |         :warning:         |      :warning:     |
| 91xx, LDS             |            :x:            |         :x:        |
| 91xx, LD              |            :x:            |         :x:        |
| 91xx, POP             |         :warning:         |      :warning:     |
| 92xx, STS             |            :x:            |         :x:        |
| 92xx, ST              |            :x:            |         :x:        |
| 92xx, PUSH            |         :warning:         |      :warning:     |
| 93xx, STS             |            :x:            |         :x:        |
| 93xx, ST              |            :x:            |         :x:        |
| 93xx, PUSH            |         :warning:         |      :warning:     |
| 94xx, MANY            |            :x:            |         :x:        |
| 95xx, MANY            |       :construction:      |         :x:        |
| 96xx, ADIW            |         :warning:         |         :x:        |
| 97xx, SBIW            |         :warning:         |         :x:        |
| 98xx, CBI             |            :x:            |         :x:        |
| 99xx, SBIC            |            :x:            |         :x:        |
| 9Axx, SBI             |            :x:            |         :x:        |
| 9Bxx, SBIS            |            :x:            |         :x:        |
| 9Cxx -> 9Fxx, MUL     |         :warning:         |         :x:        |
| A0xx -> A1xx, LDD     |         :warning:         |      :warning:     |
| A2xx -> A3xx, STD     |         :warning:         |         :x:        |
| A4xx -> A5xx, LDD     |         :warning:         |      :warning:     |
| A6xx -> A7xx, STD     |         :warning:         |         :x:        |
| A8xx -> A9xx, LDD     |         :warning:         |      :warning:     |
| AAxx -> ABxx, STD     |         :warning:         |         :x:        |
| ACxx -> ADxx, LDD     |         :warning:         |      :warning:     |
| AExx -> AFxx, STD     |         :warning:         |         :x:        |
| B0xx -> B7xx, IN      |         :warning:         |      :warning:     |
| B8xx -> BFxx, OUT     |         :warning:         |         :x:        |
| C0xx -> CFxx, RJMP    |         :warning:         |         :x:        |
| D0xx -> DFxx, RCALL   |         :warning:         |      :warning:     |
| E0xx -> EFxx, LDI     |         :warning:         |      :warning:     |
| F0xx -> F3xx, BRCS    |         :warning:         |         :x:        |
| F4xx -> F7xx, BRCC    |         :warning:         |         :x:        |
| F8xx -> F9xx, BLD     |         :warning:         |         :x:        |
| FAxx -> FBxx, BST     |         :warning:         |         :x:        |
| FCxx -> FDxx, SBRC    |         :warning:         |         :x:        |
| FExx -> FFxx, SBRS    |         :warning:         |         :x:        |


hecc.




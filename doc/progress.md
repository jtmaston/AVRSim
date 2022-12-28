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


|   OPCODE     |        DECODABLE       |  EXECUTABLE  |
|:------------ |:----------------------:|:------------:|
| 00xx, NOP    |        :warning:       |      :warning:     |
| 01xx, MOVW   |        :warning:       |      :warning:     |
| 02xx, MULS   |        :warning:       |      :x:     |
| 03xx, MULSU  |        :warning:       |      :x:     |
| 03xx, FMUL   |        :warning:       |      :x:     |
| 03xx, FMULS  |        :warning:       |      :x:     |
| 03xx, FMULSU |        :warning:       |      :x:     |
| 04xx, CPC    |        :warning:       |      :x:     |
| 05xx, CPC    |        :warning:       |      :x:     |
| 06xx, CPC    |        :warning:       |      :x:     |
| 07xx, CPC    |        :warning:       |      :x:     |
| 08xx, SBC    |        :warning:       |      :x:     |
| 09xx, SBC    |     :construction:     |      :x:     |
| 0Axx, SBC    |          :x:           |      :x:     |
| 0Bxx, SBC    |          :x:           |      :x:     |
| 0Cxx, ADD    |        :warning:       |   :warning:  |
| 0Dxx, ADD    |        :warning:       |   :warning:  |
| 0Exx, ADD    |        :warning:       |   :warning:  |
| 0Fxx, ADD    |        :warning:       |   :warning:  |
| 10xx, CPSE   |          :x:           |      :x:     |
| 11xx, CPSE   |          :x:           |      :x:     |
| 12xx, CPSE   |          :x:           |      :x:     |
| 13xx, CPSE   |          :x:           |      :x:     |
| 14xx, CP     |          :x:           |      :x:     |
| 15xx, CP     |          :x:           |      :x:     |
| 16xx, CP     |          :x:           |      :x:     |
| 17xx, CP     |          :x:           |      :x:     |
| 18xx, SUB    |          :x:           |      :x:     |
| 19xx, SUB    |          :x:           |      :x:     |
| 1Axx, SUB    |          :x:           |      :x:     |
| 1Bxx, SUB    |          :x:           |      :x:     |
| 1Cxx, ADC    |        :warning:       |      :x:     |
| 1Dxx, ADC    |        :warning:       |      :x:     |
| 1Exx, ADC    |        :warning:       |      :x:     |
| 1Fxx, ADC    |        :warning:       |      :x:     |
| 20xx, AND    |          :x:           |      :x:     |
| 21xx, AND    |          :x:           |      :x:     |
| 22xx, AND    |          :x:           |      :x:     |
| 23xx, AND    |          :x:           |      :x:     |
| 24xx, EOR    |          :x:           |      :x:     |
| 25xx, EOR    |          :x:           |      :x:     |
| 26xx, EOR    |          :x:           |      :x:     |
| 27xx, EOR    |          :x:           |      :x:     |
| 28xx, OR     |          :x:           |      :x:     |
| 29xx, OR     |          :x:           |      :x:     |
| 2Axx, OR     |          :x:           |      :x:     |
| 2Bxx, OR     |          :x:           |      :x:     |
| 2Cxx, MOV    |          :x:           |   :warning:  |
| 2Dxx, MOV    |          :x:           |   :warning:  |
| 2Exx, MOV    |          :x:           |   :warning:  |
| 2Fxx, MOV            |          :x:           |   :warning:  |
| 30xx -> 3Fxx, CPI    |          :x:           |      :x:     |
| 40xx -> 4Fxx, SBCI   |          :x:           |      :x:     |
| 50xx -> 5Fxx, SBCI   |          :x:           |      :x:     |
| 60xx -> 6Fxx, ORI    |          :x:           |      :x:     |
| 70xx -> 7Fxx, ANDI   |          :x:           |      :x:     |
| 80xx, LD    |          :x:           |      :x:     |
| 80xx, LDD   |          :x:           |   :warning:  |
| 81xx, LD    |        :warning:       |      :x:     |
| 81xx, LDD   |        :warning:       |   :warning:  |
| 82xx, ST    |          :x:           |      :x:     |
| 82xx, STD   |          :x:           |   :warning:  |
| 83xx, ST    |          :x:           |      :x:     |
| 83xx, STD   |          :x:           |   :warning:  |
| 84xx, LDD   |          :x:           |   :warning:  |
| 85xx, LDD   |          :x:           |   :warning:  |
| 86xx, STD   |          :x:           |   :warning:  |
| 87xx, STD   |          :x:           |   :warning:  |
| 88xx, LDD   |          :x:           |   :warning:  |
| 89xx, LDD   |          :x:           |   :warning:  |
| 8Axx, STD   |          :x:           |   :warning:  |
| 8Bxx, STD   |          :x:           |   :warning:  |
| 8Cxx, LDD   |          :x:           |   :warning:  |
| 8Dxx, LDD   |          :x:           |   :warning:  |
| 8Exx, STD   |          :x:           |   :warning:  |
| 8Fxx, STD   |          :x:           |   :warning:  |
| 90xx, LDS   |          :x:           |      :x:     |         
| 90xx, LD    |          :x:           |      :x:     |
| 90xx, POP   |          :x:           |      :warning:     |
| 90xx, LDS   |          :x:           |      :x:     |
| 90xx, LD    |          :x:           |      :x:     |
| 90xx, POP   |          :x:           |      :warning:     |
| 91xx, LDS   |          :x:           |      :x:     |
| 91xx, LD    |          :x:           |      :x:     |
| 91xx, POP   |        :warning:       |   :warning:  |
| 92xx, STS   |          :x:           |      :x:     |
| 92xx, ST    |          :x:           |      :x:     |
| 92xx, PUSH  |        :warning:       |   :warning:  |
| 93xx, STS   |          :x:           |      :x:     |
| 93xx, ST    |          :x:           |      :x:     |
| 93xx, PUSH  |          :x:           |   :warning:  |
| 94xx, MANY  |          :x:           |      :x:     |
| 95xx, MANY  |     :construction:     |      :x:     |
| 96xx, ADIW  |        :warning:       |      :x:     |
| 97xx, SBIW  |          :x:           |      :x:     |
| 98xx, CBI   |          :x:           |      :x:     |
| 99xx, SBIC  |          :x:           |      :x:     |
| 9Axx, SBI   |          :x:           |      :x:     |
| 9Bxx, SBIS  |          :x:           |      :x:     |
| 9Cxx -> 9Fxx, MUL  |          :x:           |      :x:     |
| A0xx -> A1xx, LDD  |          :x:           |   :warning:  |
| A2xx -> A3xx, STD  |          :x:           |      :x:     |
| A4xx -> A5xx, LDD  |          :x:           |   :warning:  |
| A6xx -> A7xx, STD  |          :x:           |      :x:     |
| A8xx -> A9xx, LDD  |          :x:           |   :warning:  |
| AAxx -> ABxx, STD  |          :x:           |      :x:     |
| ACxx -> ADxx, LDD  |          :x:           |   :warning:  |
| AExx -> AFxx, STD  |          :x:           |      :x:     |
| B0xx -> B7xx, IN   |        :warning:       |   :warning:  |
| B8xx -> BFxx, OUT  |        :warning:       |      :x:     |
| C0xx -> CFxx, RJMP |          :x:           |      :x:     |
| D0xx -> DFxx, RCALL|        :warning:       |   :warning:  |
| E0xx -> EFxx, LDI  |        :warning:       |   :warning:  |
| F0xx -> F3xx, BRCS |          :x:           |      :x:     |
| F4xx -> F7xx, BRCC |          :x:           |      :x:     |
| F8xx -> F9xx, BLD  |          :x:           |      :x:     |
| FAxx -> FBxx, BST  |          :x:           |      :x:     |
| FCxx -> FDxx, SBRC |          :x:           |      :x:     |
| FExx -> FFxx, SBRS |          :x:           |      :x:     |


hecc.




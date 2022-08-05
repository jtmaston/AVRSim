# Progress

## Aim
This document aims to present progress on implementing the ISA, differentiating between implementation at a decoder level and executable level.
The distinction appears due to how the fetch-decode-execute cycle is implemented in this simulator. Unlike in a real processor, instructions are prefetched, read from disk into the emulator's RAM before execution. Beyond faster access, there is no benefit from this, but it was chosen an interim sollution. Perhaps future versions will implement real ISA behavior

## Progress table

:x: =                      Not implemented
:interrobang: =            Partial implementation available
:heavy_exclamation_mark: = Implemented, but untested / partially tested
:white_check_mark: =       Fully implemented

|   OPCODE    |   DECODABLE            |  EXECUTABLE  |
| :--------:  | :-----------:          |:------------:|
| 00xx, NOP   |:heavy_exclamation_mark:|:x:           |
| 01xx, MOVW  |:heavy_exclamation_mark:|:x:           |
| 02xx, MULS  |:heavy_exclamation_mark:|:x:           |
| 03xx, MULSU |:heavy_exclamation_mark:|:x:           |



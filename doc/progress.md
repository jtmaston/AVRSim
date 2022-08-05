# Progress

## Aim
This document aims to present progress on implementing the ISA, differentiating between implementation at a decoder level and executable level.
The distinction appears due to how the fetch-decode-execute cycle is implemented in this simulator. Unlike in a real processor, instructions are prefetched, read from disk into the emulator's RAM before execution. Beyond faster access, there is no benefit from this, but it was chosen an interim sollution. Perhaps future versions will implement real ISA behavior

## Progress table

:x: =                      Not implemented

:construction: =            Partial implementation available

:warning: = Implemented, but untested / partially tested

:white_check_mark: =       Fully implemented


|   OPCODE     |        DECODABLE       |  EXECUTABLE  |
|:------------ |:----------------------:|:------------:|
| 00xx, NOP    |        :warning:       |      :x:     |
| 01xx, MOVW   |        :warning:       |      :x:     |
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



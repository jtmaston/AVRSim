//
//  Processor.hpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//


/**
 *  Describes the processor itself. The target ( for now ) is to attempt to emulate an ATMEGA328p, with final
 *  goals being having an adaptable interpreter, based on the MCU needed.
 
 */

#pragma once

// implement AVR5

#include <inttypes.h>
#include "fetcher.hpp"
#include "Executable.hpp"
#include "avr.hpp"


#define REG_X 33        // special registers X[r27, r26],
#define REG_Y 34        // Y[r29:r28],
#define REG_Z 35        // and Z[r31:r30] are mapped to a range outside of the
                        // usual 32 registers, in order to much more easily
                        // tell the program that they are being used.

struct Processor
{
    uint8_t gp_registers[32];     // General purpose working registers, 32x8bit
    
    uint8_t IO_registers[64];       // I/O registers, of which 64 exist
    uint8_t EXT_IO_registers[160];  // extended I/O registers
    
    uint16_t PC = 0;                // program counter
    uint16_t SP = 2048;             // stack pointer
    uint8_t SREG;                   // status register, implemented as a byte

    uint8_t SRAM[2048];             // 2KB ( kilobytes ) SRAM

    std::vector<Executable> progmem; // program memory, contains the loaded
                                     // program. vaguely equates to FLASH mem.
    void execute(Executable e);

    uint16_t read_X();              // macro to read the "X" register
    uint16_t read_Y();              // macro to read the "Y" register
    uint16_t read_Z();              // macro to read the "Z" register

    bool write_X(uint16_t value);   // ditto for writing
    bool write_Y(uint16_t value);
    bool write_Z(uint16_t value);
};

/*
    SREG MAPPING
    |     0      |     1     |       2       |        3        |
    | Carry Flag | Zero flag | Negative flag |  Overflow flag  |
 
    |     4      |        5        |    6     |       7        |
    | Sign flag  | Half-carry flag | Bit copy | Interrupt flag |
*/

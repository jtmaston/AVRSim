//
//  Decoder.hpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//


/**
 *  Describes stage two of the pipeline, the decoding phase. Instructions identified by their opcodes are
 *      transformed into their corresponding machine instructions, ready to be interpreted by the emulator.
 *  This task often refers to mapping a hex value to a register number, or a certain hex combination to a
 *      constant value. Opcodes were implemented using the helpful table which can be found at
 *      http://lyons42.com/AVR/Opcodes/AVRAllOpcodes.html.
 
 */

#pragma once

#include "fetcher.hpp"
#include "avr.hpp"
#include "processor.hpp"
#include "fetcher.hpp"

struct Decoder
{
    Processor* CPU;                             // a pointer to the active CPU
    bool decode(const Instruction instruction); // decode an instruction
    bool decodeRecord(Record r);                // decode a record ( collection
};                                              // of instructions )

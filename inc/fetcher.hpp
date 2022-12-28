//
//  Fetcher.hpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//


/**
 
 * Describes the Fetcher class, first part of our three-stage pipeline.
 * The fetcher has the task of extracting a record from the .hex file and decoding the arguments
 *  contained within. Note that the fetcher itself does not decode *instructions*, but rather records.
 
 */


#ifndef FETCHER_H
#define FETCHER_H
#include <inttypes.h>
#include <fstream>
#include <vector>

struct Instruction              // defines the final Instruction object,
{                               // composed of an opcode ( as described by the
    uint16_t opcode;             // AVR5 ISA.
    uint8_t arg;
};

struct Record                   // defines an incoming record, in the format
{                               // of Intel HEX
    uint8_t record_length;      // Thus, record length
    uint16_t address;           // Record Address
    uint8_t type;               // Type of record
    uint8_t data[100][2];       // The actual data array, expecting instructions
                                //  to be 2 bytes wide
    uint8_t checksum;           // and the integrity checksum.


    std::vector<Instruction> instruction_data;     // array of instructions
    bool loadNextRecord(std::fstream &input);      // loads new record from file
};


#endif

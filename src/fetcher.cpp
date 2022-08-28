//
//  Fetcher.cpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//

// -> see https://en.wikipedia.org/wiki/Intel_HEX

#include "fetcher.hpp"

uint8_t twos_complement(uint8_t val)    // used in record checksum calculation
{
    return -(unsigned int)val;
}

bool Record::loadNextRecord(std::fstream &input)        // loads a record
{
    std::string line;
    getline(input, line);               // get the line

    if(line.size() == 0)                // do a sanity check
        return false;

    if (line.at(0) != ':')              // check if binary is in Intel Hex fmt.
        throw std::runtime_error("HEX Format error!");

    Record inbound;                     // get incoming record data
    inbound.record_length = std::stoi(line.substr(1, 2), 0, 16);
    inbound.address = std::stoi(line.substr(3, 4), 0, 16);
    inbound.type = std::stoi(line.substr(7, 2), 0, 16);

    uint8_t checksum = inbound.record_length + inbound.address + inbound.type;
    // ^ start calculating the checksum
    
    for (int i = 0; i < inbound.record_length * 2; i += 4) // read each instr.
    {
        Instruction instruction;

        instruction.opcode = std::stoi(line.substr(9 + i + 2, 2), 0, 16);
        instruction.arg = std::stoi(line.substr(9 + i, 2), 0, 16);
        instruction_data.push_back(std::move(instruction));
        checksum += instruction.opcode + instruction.arg;
    }
    //  ^ converts each instruction into numeric values

    inbound.checksum = std::stoi(line.substr(line.length() - 3, 2), 0, 16);

    if (inbound.checksum != twos_complement(checksum))    // do checksum check
        throw std::runtime_error("Checksum miss-match in hex file!");

    return true;
}


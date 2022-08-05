#ifndef FETCHER_H
#define FETCHER_H
#include <inttypes.h>
#include <fstream>
#include <vector>

struct Instruction
{
    uint8_t opcode;
    uint8_t arg;
};

struct Record
{
    uint8_t record_length;
    uint16_t address;
    uint8_t type;
    uint8_t data[100][2];
    uint8_t checksum;


    std::vector<Instruction> instruction_data;
    bool loadNextRecord(std::fstream &input);
};


#endif
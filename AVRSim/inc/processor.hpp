#pragma once

// implement AVR5

#include <inttypes.h>
#include "fetcher.hpp"
#include "Executable.hpp"
#include "avr.hpp"


#define REG_X 33
#define REG_Y 34
#define REG_Z 35

struct Processor
{
    uint8_t gpio_registers[32]; // gpio registers
    
    uint8_t IO_registers[64];
    uint8_t EXT_IO_registers[160];
    
    uint16_t PC;                // program counter
    uint16_t SP;                // stack pointer
    uint8_t SREG;               // status register

    uint8_t SRAM[2000]; // 2KB ( kilobytes ) SRAM

    std::vector<Executable> progmem;
    void execute(Executable e);

    uint16_t read_X();
    uint16_t read_Y();
    uint16_t read_Z();

    bool write_X(uint16_t value);
    bool write_Y(uint16_t value);
    bool write_Z(uint16_t value);
};

/*
    SREG MAPPING
    |     0      |     1     |       2       |       3       |     4     |        5        |    6     |       7        |
    | Carry Flag | Zero flag | Negative flag | Overflow flag | Sign flag | Half-carry flag | Bit copy | Interrupt flag |
*/

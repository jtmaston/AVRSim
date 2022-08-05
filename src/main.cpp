//
//  main.cpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 3/8/22.
//


#include <iostream>
#include "fetcher.hpp"
#include "registers.hpp"
#include "decoder.hpp"
#include "processor.hpp"

#include <fstream>

#include <stdint.h>

#include <chrono>
#include <cstring>

int main()
{
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    using std::chrono::microseconds;
    
    Decoder decoder;
    Record fetcher;
    
    Processor CPU;
    decoder.CPU = &CPU;
    
    std::fstream fin("test.hex", std::fstream::in);
    
    CPU.gpio_registers[26] = (uint8_t)0b01010101;
    CPU.gpio_registers[27] = (uint8_t)0b10101010;
    
    auto t1 = high_resolution_clock::now();
    while(!fin.eof())
    {
        fetcher.loadNextRecord(fin);
        decoder.decodeRecord(fetcher);
        
    }
    
    uint16_t PROGMEM_SIZE = CPU.progmem.size();
    memset(CPU.gpio_registers, 32, sizeof(uint8_t));
    memset(CPU.SRAM, 2000, sizeof(uint8_t));
    CPU.PC = 0;
    CPU.SP = 0;
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<microseconds>(t2 - t1);
    std::cout << "Finished loading and initialization in " << ms_int.count() << "us\n";
    
    while( CPU.PC < PROGMEM_SIZE )
    {
        
        CPU.PC++;
    }
    
    return 0;
}

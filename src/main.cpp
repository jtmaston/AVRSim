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
    
    // * << this whole block is garbage, needs removal / moving away
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    using std::chrono::microseconds;
    // * >>
    
    Decoder decoder;
    Record fetcher;
    
    Processor CPU;
    decoder.CPU = &CPU;
    
    std::fstream fin("test.hex", std::fstream::in);  // open file
    
    auto t1 = high_resolution_clock::now();
    while(!fin.eof())                               // fetch-decode cycle
    {
        fetcher.instruction_data.clear();
        if(fetcher.loadNextRecord(fin))
        {
            decoder.decodeRecord(fetcher);
        }
    }
    
    uint16_t PROGMEM_SIZE = CPU.progmem.size();     // compute once, to aviod
                                                    // repeated calls in while
    
    memset(CPU.gpio_registers, 0, 32 * sizeof(uint8_t));    // clear regs
    memset(CPU.SRAM, 0, 2048 * sizeof(uint8_t));            // clear SRAM

    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<microseconds>(t2 - t1);
    std::cout << "Finished loading and initialization in "
        << ms_int.count() << "us\n";
    
    t1 = high_resolution_clock::now();
    while( CPU.PC < PROGMEM_SIZE )                  // the execute cycle
    {
        CPU.execute(CPU.progmem.at(CPU.PC));
    }
    t2 = high_resolution_clock::now();
    ms_int = duration_cast<microseconds>(t2 - t1);
    
    
    std::cout << "Program returned " <<
        (CPU.gpio_registers[25] << 8 | CPU.gpio_registers[24]) << '\n';
    
    std::cout << "Finished executing in " << ms_int.count() << "us\n";
    
    return 0;
}

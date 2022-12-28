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

#include <util.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/stat.h>

#include <chrono>
using namespace std::chrono;

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
    
    //int master;
    //int slave;
    //char slave_name[100];
    
    /*openpty(&master, &slave, slave_name, NULL, NULL);
    std::cout << "Serial redirects to " << slave_name << std::endl;
    int fd;
    if ((fd = open(slave_name, O_RDWR|O_NDELAY|O_NOCTTY)) < 0)
            return -1;
    
    int flags;
    flags = fcntl(fd, F_GETFL, 0);
    tcflush(fd, TCOFLUSH);
    tcflush(fd, TCIFLUSH);

    while(true){
        char buf[1000] = { 0 };
        struct stat filestats;
        fstat(fd, &filestats);
        if ( filestats.st_size > 0 )
            std::cout << "Filesize is " << filestats.st_size << std::endl;
        
        
        if ( !(read(fd, buf, 1000) < 0 ) )
        {
            std :: cout << "Incoming: " << buf << std::endl;
        }
    };*/
    
    /*openpty(&master, &slave, slave_name, NULL, NULL);
    std::cout << "Slave serial redirects to " << slave_name << std::endl;
    
    
    // TODO: check if valid for different baudrates
    const int baudrate = 9600;
    float baudate_time = (float) (1e6) / (baudrate / 8.0f );
    
    auto start = high_resolution_clock::now();
    while (true) {
        char buf[3] = { 0 };
        if( read(master, buf, 1) > 0 )
        {
            //std::cout << "Incoming: " << buf << '\n';
        }
        auto stop = high_resolution_clock::now();
        if( duration_cast<microseconds>(stop - start).count() < baudate_time )
        {
            usleep(baudate_time - duration_cast<microseconds>(stop - start).count());
        }
            
        start = high_resolution_clock::now();
    }
    close(master);
    close(slave);*/
    //return 0;
}

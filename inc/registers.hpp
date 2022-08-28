//
//  Registers.hpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//

// !!WIP!!

#ifndef AVRSIM_REGISTERS
#define AVRSIM_REGISTERS

#include <inttypes.h>

struct GPRegisterBank{
    int8_t registers[32];
}gpr;

struct StatusRegisterBank{
    bool C;                     // carry flag
    bool Z;                     // zero flag
    bool N;                     // negative flag
    bool V;                     // 2 complement overflow
    bool S;                     // signed
    bool H;                     // half carry
    bool T;                     // transfer bit
    bool I;                     // global interrupt enable
};

#endif

//
//  Executable.hpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//

#ifndef Executable_hpp
#define Executable_hpp

#include <inttypes.h>

struct Executable {
    uint8_t instruction_num;
    uint8_t* operand_1;
    uint8_t* operand_2;
    int16_t offset;
};
#endif /* Executable_hpp */

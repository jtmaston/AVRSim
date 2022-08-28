//
//  Executable.hpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//

/**
 *  Describes the interpretable instruction, as ready to be run.
 
 */


#ifndef Executable_hpp
#define Executable_hpp

#include <inttypes.h>

struct Executable {
    uint8_t instruction_num;    // the internal opcode, mapped to avr.hpp
    uint8_t* operand_1;         // the first operand of an instruction.
                                // pointer to the register used
    uint8_t* operand_2;         // ditto
    int16_t offset;             // in case of a literal, the "offset" is used
};
#endif /* Executable_hpp */

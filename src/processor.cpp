//
//  Processor.cpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//





#include "processor.hpp"

#include <iostream>


uint16_t Processor::read_X()
{
    return ( gpio_registers[27] << 8 ) | gpio_registers[26];
}
uint16_t Processor::read_Y()
{
    return ( gpio_registers[29] << 8 ) | gpio_registers[28];
}
uint16_t Processor::read_Z()
{
    return ( gpio_registers[31] << 8 ) | gpio_registers[30];
}

bool Processor::write_X(uint16_t value)
{
    gpio_registers[27] = value >> 8;
    gpio_registers[26] = value;
    return true;
}
bool Processor::write_Y(uint16_t value)
{
    gpio_registers[29] = value >> 8;
    gpio_registers[28] = value;
    return true;
}
bool Processor::write_Z(uint16_t value)
{
    gpio_registers[31] = value >> 8;
    gpio_registers[30] = value;
    return true;
}

void Processor::execute(Executable e)   // takes an executable and runs it
{                                       // see AVR ISA for implementation.
    switch ( e.instruction_num) {
            
        case PUSH:
        {
            SRAM[SP--] = *e.operand_1;
            PC++;
            break;
        }
        
        case POP:
        {
            *e.operand_1 = SRAM[SP++];
            PC++;
            break;
        }
            
        case RCALL:
        {
            SP -= 2;
            PC = PC + e.offset + 1;
            break;
        }
        case IN:
        {
            *e.operand_1 = e.offset;
            PC++;
            break;
        }
        case LDI:
        {
            *e.operand_1 = e.offset;
            PC++;
            break;
        }
        case STD:
        {
            switch ( uint8_t(e.operand_1 - gpio_registers) )
            {
                case REG_Y:
                {
                    switch( read_Y() )
                    {
                        case 0x3e3d:
                        {
                            SRAM[SP + e.offset] = *e.operand_2;
                            break;
                        }
                    }
                    break;
                }
            }
            PC++;
            break;
        }
            
        case LDD:
        {
            switch ( uint8_t(e.operand_2 - gpio_registers) )
            {
                case REG_Y:
                {
                    switch( read_Y() )
                    {
                        case 0x3e3d:
                        {
                            *e.operand_1 = SRAM[SP + e.offset];
                            break;
                        }
                    }
                    break;
                }
            }
            PC++;
            break;
        }
        case ADD:
        {
            
            *e.operand_1 = *e.operand_1 + *e.operand_2;
            PC++;
            break;
        }
        
        case RET:
        {
            SP += 2;
            PC++;
            break;
        }
            
        case MOV:
        {
            *e.operand_1 = *e.operand_2;
            PC++;
            break;
        }
            
        default:                // default case, to catch unimplemented instrs.
        {
            std::cerr << "Unrecognized instruction!";
            throw std::runtime_error("FCK");
            break;
        }
    }
}

//
//  Processor.cpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//





#include "processor.hpp"

#include <iostream>

#define M_Rd *e.operand_1
#define M_Rr *e.operand_2
#define M_Rk e.offset

uint16_t Processor::read_X()
{
    return ( gp_registers[27] << 8 ) | gp_registers[26];
}
uint16_t Processor::read_Y()
{
    return ( gp_registers[29] << 8 ) | gp_registers[28];
}
uint16_t Processor::read_Z()
{
    return ( gp_registers[31] << 8 ) | gp_registers[30];
}

bool Processor::write_X(uint16_t value)
{
    gp_registers[27] = value >> 8;
    gp_registers[26] = value;
    return true;
}
bool Processor::write_Y(uint16_t value)
{
    gp_registers[29] = value >> 8;
    gp_registers[28] = value;
    return true;
}
bool Processor::write_Z(uint16_t value)
{
    gp_registers[31] = value >> 8;
    gp_registers[30] = value;
    return true;
}

void Processor::execute(Executable e)   // takes an executable and runs it
{                                       // see AVR ISA for implementation.
    // TODO: set SREG
    switch ( e.instruction_num) {
            
        case PUSH:
        {
            SRAM[SP--] = M_Rd;
            PC++;
            break;
        }
        
        case POP:
        {
            M_Rd = SRAM[SP++];
            PC++;
            break;
        }
            
        case RCALL:
        {
            SP -= 2;                // TODO: store return address on the stack
            SRAM[SP--] = (uint8_t) PC >> 8;
            SRAM[SP--] = (uint8_t) ( PC & 0xFF );
            PC = PC + M_Rk + 1;
            break;
        }
        case RJMP:
        {
            PC = PC + M_Rk + 1;
            break;
        }
        case IN:
        {
            //*e.operand_1 = e.offset;  TODO: reimplement
            PC++;
            break;
        }
        case LDI:
        {
            M_Rd = M_Rk;
            PC++;
            break;
        }
        case STD:
        {
            /*switch ( uint8_t(e.operand_1 - gp_registers) )
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
            }*/
            
            PC++;
            break;
        }
            
        case LDD:
        {
            switch ( uint8_t(e.operand_2 - gp_registers) )
            {
                case REG_Y:
                {
                    /*switch( read_Y() )
                    {
                        case 0x3e3d:
                        {
                            *e.operand_1 = SRAM[SP + e.offset];
                            break;
                        }
                    }*/
                    
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
        case NOP:
        {
            PC++;
            break;
        }
        case MOVW:
        {
            *e.operand_1 = *e.operand_2;        // TODO: investigate
            *e.operand_2 = *e.operand_2;
            PC++;
            break;
        }
        case MULS:
        case MULSU:
        {
            int16_t res = (*e.operand_1) * (*e.operand_2);
            gp_registers[0] = (uint8_t) res;
            gp_registers[1] = (uint8_t) (res >> 8);
            if(!res)
                SREG = SREG | 0b00000010;   // set zero flag
            PC++;
            break;
            
        }
        case EOR:
        {
            M_Rd = M_Rd ^ M_Rr;
            PC++;
            break;
        }
        case COM:
        {
            M_Rd = 0xFF - M_Rd;
            PC++;
            break;
        }
        case OUT:
        {
            PC++;
            break;
        }
        
            
        default:                // default case, to catch unimplemented instrs.
        {
            throw std::runtime_error("Instruction not implemented for execution!");
            break;
        }
    }
}

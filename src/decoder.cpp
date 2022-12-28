//
//  Decoder.cpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//


#include "decoder.hpp"
#include <iostream>
#include <sstream>

bool Decoder::decode(const Instruction instruction)
{
    Executable e;
    
    int16_t offset_1 = -1;              // offsets from the main
    int16_t offset_2 = -1;              // gpio_registers pointer
    
    switch (instruction.opcode)         // implement opcodes, following the ISA
    {
        case 0x00:
        {
            e.instruction_num = NOP;
            offset_1 = -1;
            offset_2 = -1;
            break;
        }
        case 0x01:
        {
            e.instruction_num = MOVW;
            offset_1 = (((instruction.arg & 0xf0) >> 4) * 2);
            offset_2 = ((instruction.arg & 0x0f) * 2);
            break;
        }
        case 0x02:
        {
            e.instruction_num = MULS;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = ((instruction.arg & 0x0f) + 16);
            break;
        }
        case 0x03:
        {
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = ((instruction.arg & 0x0f) + 16);
            
            if (offset_1 < 8 && offset_2 < 8)
            {
                e.instruction_num = MULSU;
            }
            else if (offset_1 >= 8 && offset_2 < 8)
            {
                e.instruction_num = FMULS;
                offset_1 -= 8;
            }
            else if (offset_1 < 8 && offset_2 >= 8)
            {
                e.instruction_num = FMUL;
                offset_2 -= 8;
            }
            else if (offset_1 >= 8 && offset_2 >= 8)
            {
                e.instruction_num = FMULSU;
                offset_1 -= 8;
                offset_2 -= 8;
            }
            else
            {
                throw std::runtime_error("Unimplemented!");
            }
            break;
        }
        case 0x04:
        {
            e.instruction_num = CPC;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
            
        case 0x05:
        {
            e.instruction_num = CPC;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x06:
        {
            e.instruction_num = CPC;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f) + 16);
            break;
        }
        case 0x07:
        {
            e.instruction_num = CPC;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = ((instruction.arg & 0x0f) + 16);
            break;
        }
        case 0x08:
        {
            e.instruction_num = SBC;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        
        case 0x92:
        {
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            
            switch(offset_2)
            {
                case 0xF:
                {
                    e.instruction_num = PUSH;
                    offset_2 = -1;
                    break;
                }
            }
            
            break;
        }
            
        case 0x93:
        {
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            
            switch(offset_2)
            {
                case 0xF:
                {
                    e.instruction_num = PUSH;
                    offset_1 += 16;
                    offset_2 = -1;
                    break;
                }
            }
            
            break;
        }
            
        case 0x81:
        {
            if ( ( instruction.arg & 0x0f ) < 8 )
            {
                if ( instruction.arg == 0 )
                {
                    e.instruction_num = LD;
                    offset_2 = REG_Z;
                    offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
                    e.offset = 0;
                    
                }else
                {
                    e.instruction_num = LDD;
                    offset_2 = REG_Z;
                    offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
                    e.offset = instruction.arg & 0x0f;
                }
            } else
            {
                if ( (instruction.arg & 0x0f) == 0x08 )
                {
                    e.instruction_num = LD;
                    offset_2 = REG_Y;
                    offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
                    e.offset = 0;
                    
                }else
                {
                    e.instruction_num = LDD;
                    offset_2 = REG_Y;
                    offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
                    e.offset = instruction.arg & 0x0f - 8;
                }
            }
            break;
        }
            
        case 0x83:
        {
            
            if ( ( instruction.arg & 0x0f ) < 8 )
            {
                if ( instruction.arg == 0 )
                {
                    e.instruction_num = ST;
                    offset_1 = REG_Z;
                    offset_2 = (((instruction.arg & 0xf0) >> 4) + 16);
                    e.offset = 0;
                    
                }else
                {
                    e.instruction_num = STD;
                    offset_1 = REG_Z;
                    offset_2 = (((instruction.arg & 0xf0) >> 4) + 16);
                    e.offset = instruction.arg & 0x0f;
                }
            } else
            {
                if ( (instruction.arg & 0x0f) == 0x08 )
                {
                    e.instruction_num = ST;
                    offset_1 = REG_Y;
                    offset_2 = (((instruction.arg & 0xf0) >> 4) + 16);
                    e.offset = 0;
                    
                }else
                {
                    e.instruction_num = STD;
                    offset_1 = REG_Y;
                    offset_2 = (((instruction.arg & 0xf0) >> 4) + 16);
                    e.offset = instruction.arg & 0x0f - 8;
                }
            }
            break;
            
        }
            
        case 0xD0:
        case 0xD1:
        case 0xD2:
        case 0xD3:
        case 0xD4:
        case 0xD5:
        case 0xD6:
        case 0xD7:
        case 0xD8:
        case 0xD9:
        case 0xDA:
        case 0xDB:
        case 0xDC:
        case 0xDD:
        case 0xDE:
        case 0xDF:
        {
            e.instruction_num = RCALL;
            offset_1 = -1;
            offset_2 = -1;
            
            if ( instruction.opcode < 0xD8 )
            {
                uint8_t factor = instruction.opcode & 0x0F;
                e.offset = factor * 512 + instruction.arg * 2;
            }
            else
            {
                uint8_t factor = (instruction.opcode - 0xD8 ) & 0x0F;
                e.offset = -(4096 - factor * 512 - instruction.arg * 2);
            }
            
            break;
        }
            
        case 0xB0:
        case 0xB1:
        case 0xB2:
        case 0xB3:
        case 0xB4:
        case 0xB5:
        case 0xB6:
        case 0xB7:
        {
            e.instruction_num = IN;
            uint8_t register_factor = (( instruction.opcode - 0xB0 ) % 2 ) * 16;
            offset_1 =(((instruction.arg & 0xf0) >> 4)) + register_factor;
            offset_2 = -1;
            
            
            if ( (instruction.opcode & 0x0f) % 2)
            {
                e.offset = (( instruction.opcode - 0xB1 ) / 2) << 4;
                e.offset = e.offset | ( 0x0F & instruction.arg );
            }else
            {
                e.offset = (( instruction.opcode - 0xB0 ) / 2) << 4;
                e.offset = e.offset | ( 0x0F & instruction.arg );
            }
            break;
        }
            
        case 0xE0:
        case 0xE1:
        case 0xE2:
        case 0xE3:
        case 0xE4:
        case 0xE5:
        case 0xE6:
        case 0xE7:
        case 0xE8:
        case 0xE9:
        case 0xEA:
        case 0xEB:
        case 0xEC:
        case 0xED:
        case 0xEE:
        case 0xEF:
        {
            e.instruction_num = LDI;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = -1;
            e.offset = ((instruction.opcode & 0x0f ) << 4 )| ( instruction.arg & 0x0f );
            
            break;
        }
            
        case 0x0C:
        {
            e.instruction_num = ADD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x0D:
        {
            e.instruction_num = ADD;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x0E:
        {
            e.instruction_num = ADD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x0F:
        {
            e.instruction_num = ADD;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
            
        case 0x1C:
        {
            e.instruction_num = ADC;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x1D:
        {
            e.instruction_num = ADC;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x1E:
        {
            e.instruction_num = ADC;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x1F:
        {
            e.instruction_num = ADC;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
            
        case 0x96:
        {
            e.instruction_num = ADIW;
            offset_1 = (( instruction.arg >> 4 ) % 4 ) * 2 + 24;
            offset_2 = -1;
            e.offset = (( instruction.arg >> 4 ) / 4 ) * 0x10 + ((instruction.arg & 0x0f));
            
            break;
        }
        case 0x94:
        {
            switch( instruction.arg & 0xf0)
            {
                case 0:
                {
                    e.instruction_num = COM;
                    offset_1 = instruction.arg >> 4;
                    offset_2 = 0;
                    break;
                }
                case 1:
                {
                    e.instruction_num = NEG;
                    offset_1 = instruction.arg >> 4;
                    offset_2 = 0;
                    break;
                }
                case 2:
                {
                    e.instruction_num = SWAP;
                    offset_1 = instruction.arg >> 4;
                    offset_2 = 0;
                    break;
                }
                case 3:
                {
                    e.instruction_num = INC;
                    offset_1 = instruction.arg >> 4;
                    offset_2 = 0;
                    break;
                }
                case 5:
                {
                    e.instruction_num = ASR;
                    offset_1 = instruction.arg >> 4;
                    offset_2 = 0;
                    break;
                }
                case 6:
                {
                    e.instruction_num = LSR;
                    offset_1 = instruction.arg >> 4;
                    offset_2 = 0;
                    break;
                }
                case 7:
                {
                    e.instruction_num = ROR;
                    offset_1 = instruction.arg >> 4;
                    offset_2 = 0;
                    break;
                }
                case 0xA:
                {
                    e.instruction_num = DEC;
                    offset_1 = instruction.arg >> 4;
                    offset_2 = 0;
                    break;
                }
                case 8:
                {
                    switch ( instruction.arg >> 4 )
                    {
                        case 0:
                        {
                            e.instruction_num = SEC;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 1:
                        {
                            e.instruction_num = SEZ;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 2:
                        {
                            e.instruction_num = SEN;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 3:
                        {
                            e.instruction_num = SEV;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 4:
                        {
                            e.instruction_num = SES;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 5:
                        {
                            e.instruction_num = SEH;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 6:
                        {
                            e.instruction_num = SET;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 7:
                        {
                            e.instruction_num = SEI;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 8:
                        {
                            e.instruction_num = CLC;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 9:
                        {
                            e.instruction_num = CLZ;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 10:
                        {
                            e.instruction_num = CLN;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 11:
                        {
                            e.instruction_num = CLV;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 12:
                        {
                            e.instruction_num = CLS;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 13:
                        {
                            e.instruction_num = CLH;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 14:
                        {
                            e.instruction_num = CLT;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        case 15:
                        {
                            e.instruction_num = CLI;
                            offset_1 = 0;
                            offset_2 = 0;
                            break;
                        }
                        default:
                        {
                            offset_1 = -1;
                            offset_2 = -1;
                            throw std::runtime_error("FCK");
                            break;
                        }
                    }
                }
            }
            break;
        }
            
        case 0xB8:
        case 0xB9:
        case 0xBA:
        case 0xBB:
        case 0xBC:
        case 0xBD:
        case 0xBE:
        case 0xBF:
        {
            e.instruction_num = OUT;
            uint8_t register_factor = (( instruction.opcode - 0xB0 ) % 2 ) * 16;
            offset_1 = -1;
            offset_2 = (((instruction.arg & 0xf0) >> 4)) + register_factor;
            
            
            if ( (instruction.opcode & 0x0f) % 2)
            {
                e.offset = (( instruction.opcode - 0xB9 ) / 2) << 4;
                e.offset = e.offset | ( 0x0F & instruction.arg );
            }else
            {
                e.offset = (( instruction.opcode - 0xB8 ) / 2) << 4;
                e.offset = e.offset | ( 0x0F & instruction.arg );
            }
            
            
            
            break;
        }
        case 0x90:
        {
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            
            switch(offset_2)
            {
                case 0xF:
                {
                    e.instruction_num = POP;
                    offset_2 = -1;
                    break;
                }
            }
            
            break;
        }
            
        case 0x91:
        {
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            
            switch(offset_2)
            {
                case 0xF:
                {
                    e.instruction_num = POP;
                    offset_1 += 16;
                    offset_2 = -1;
                    break;
                }
            }
            
            break;
        }
        
        
        case 0x95:
        {
            e.instruction_num = RET;
            offset_1 = -1;
            offset_2 = -1;
            // FIXME: i am too lazy to implement all these worthless instructions. But I will have to do it one day.
            break;
        }
            
        case 0x2f:                      // FIXME: this is a quick shit done to work fast, not smart. This will be properly
        {                               // implemented one day
            e.instruction_num = MOV;
            offset_1 = 24;
            offset_2 = 24;
            break;
        }
            
        default:
        {
            std::stringstream ss;
            ss << "0x" << std::hex << (int)instruction.opcode << (int)instruction.arg;
            
            std::cout << "Hits: " << CPU->progmem.size() << '\n';
            throw std::runtime_error("Unimplemented: " + ss.str());
        }
            
    }
    
    e.operand_1 = CPU->gpio_registers + offset_1;
    e.operand_2 = CPU->gpio_registers + offset_2;
    
    CPU->progmem.push_back(std::move(e));
    return true;
}

bool Decoder::decodeRecord(Record r)
{
    for (const Instruction &instruction : r.instruction_data)
    {
        decode(instruction);
    }
    return true;
}

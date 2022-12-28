//
//  Decoder.cpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//


#include "decoder.hpp"
#include <iostream>
#include <sstream>
#include <unordered_map>

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
            /*case 0x08:
             {
             e.instruction_num = SBC;
             offset_1 = (((instruction.arg & 0xf0) >> 4));
             offset_2 = ((instruction.arg & 0x0f));
             break;
             }*/
            
        case 0x80:
        {
            if ( ( instruction.arg & 0x0f ) < 8 )
            {
                if ( instruction.arg == 0 )
                {
                    e.instruction_num = LD;
                    offset_2 = REG_Z;
                    offset_1 = (((instruction.arg & 0xf0) >> 4));
                    e.offset = 0;
                    
                }else
                {
                    e.instruction_num = LDD;
                    offset_2 = REG_Z;
                    offset_1 = (((instruction.arg & 0xf0) >> 4));
                    e.offset = instruction.arg & 0x0f;
                }
            } else
            {
                if ( (instruction.arg & 0x0f) == 0x08 )
                {
                    e.instruction_num = LD;
                    offset_2 = REG_Y;
                    offset_1 = (((instruction.arg & 0xf0) >> 4));
                    e.offset = 0;
                    
                }else
                {
                    e.instruction_num = LDD;
                    offset_2 = REG_Y;
                    offset_1 = (((instruction.arg & 0xf0) >> 4));
                    e.offset = instruction.arg & 0x0f - 8;
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
            
        case 0x82:
        {
            
            if ( ( instruction.arg & 0x0f ) < 8 )
            {
                if ( instruction.arg == 0 )
                {
                    e.instruction_num = ST;
                    offset_1 = REG_Z;
                    offset_2 = (((instruction.arg & 0xf0) >> 4));
                    e.offset = 0;
                    
                }else
                {
                    e.instruction_num = STD;
                    offset_1 = REG_Z;
                    offset_2 = (((instruction.arg & 0xf0) >> 4));
                    e.offset = instruction.arg & 0x0f;
                }
            } else
            {
                if ( (instruction.arg & 0x0f) == 0x08 )
                {
                    e.instruction_num = ST;
                    offset_1 = REG_Y;
                    offset_2 = (((instruction.arg & 0xf0) >> 4));
                    e.offset = 0;
                    
                }else
                {
                    e.instruction_num = STD;
                    offset_1 = REG_Y;
                    offset_2 = (((instruction.arg & 0xf0) >> 4));
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
            
        case 0x84:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 8;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x85:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 8;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x86:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 8;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x87:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 8;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
            
        case 0x88:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 16;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x89:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 16;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x8A:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 16;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x8B:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 16;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
            
        case 0x8C:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 24;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x8D:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 24;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x8E:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 24;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0x8F:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 24;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
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
            
        case 0xC0:
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC4:
        case 0xC5:
        case 0xC6:
        case 0xC7:
        case 0xC8:
        case 0xC9:
        case 0xCA:
        case 0xCB:
        case 0xCC:
        case 0xCD:
        case 0xCE:
        case 0xCF:
        {
            e.instruction_num = RJMP;
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
            
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
        {
            e.instruction_num = CPI;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = -1;
            e.offset = ((instruction.opcode & 0x0f ) << 4 )| ( instruction.arg & 0x0f );
            
            break;
        }
            
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
        {
            e.instruction_num = SBCI;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = -1;
            e.offset = ((instruction.opcode & 0x0f ) << 4 )| ( instruction.arg & 0x0f );
            
            break;
        }
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5A:
        case 0x5B:
        case 0x5C:
        case 0x5D:
        case 0x5E:
        case 0x5F:
        {
            e.instruction_num = SUBI;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = -1;
            e.offset = ((instruction.opcode & 0x0f ) << 4 )| ( instruction.arg & 0x0f );
            
            break;
        }
            
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6A:
        case 0x6B:
        case 0x6C:
        case 0x6D:
        case 0x6E:
        case 0x6F:
        {
            e.instruction_num = ORI;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = -1;
            e.offset = ((instruction.opcode & 0x0f ) << 4 )| ( instruction.arg & 0x0f );
            
            break;
        }
            
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x7B:
        case 0x7C:
        case 0x7D:
        case 0x7E:
        case 0x7F:
        {
            e.instruction_num = ANDI;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            offset_2 = -1;
            e.offset = ((instruction.opcode & 0x0f ) << 4 )| ( instruction.arg & 0x0f );
            
            break;
        }
            
        case 0x08:
        {
            e.instruction_num = SBC;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x09:
        {
            e.instruction_num = SBC;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x0A:
        {
            e.instruction_num = SBC;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x0B:
        {
            e.instruction_num = SBC;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
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
        case 0x90:          // TODO: implement, will not at this time
        {
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            
            switch(offset_2)
            {
                case 0x00:
                {
                    std::runtime_error("Two-word instructions not supported!");
                    break;
                }
                case 0x01:
                {
                    e.instruction_num = LD;
                    offset_2 = REG_Z;
                    std::runtime_error("WIP");      // TODO: implement increment / post-increment
                }
                case 0x02:
                {
                    e.instruction_num = LD;
                    offset_2 = REG_Z;
                    std::runtime_error("WIP");
                }
                case 0x04:
                {
                    e.instruction_num = LPM;
                    offset_2 = REG_Z;
                }
                case 0x05:
                {
                    e.instruction_num = LPM;
                    offset_2 = REG_Z;
                    std::runtime_error("WIP");      // TODO: implement increment / post-increment
                }
                case 0x06:
                {
                    e.instruction_num = ELPM;
                    offset_2 = REG_Z;
                }
                case 0x07:
                {
                    e.instruction_num = ELPM;
                    offset_2 = REG_Z;
                    std::runtime_error("WIP");
                }
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
            
        case 0x95:
        {
            e.instruction_num = RET;
            offset_1 = -1;
            offset_2 = -1;
            // FIXME: i am too lazy to implement all these worthless instructions. But I will have to do it one day.
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
            
        case 0x97:
        {
            e.instruction_num = SBIW;
            offset_1 = (( instruction.arg >> 4 ) % 4 ) * 2 + 24;
            offset_2 = -1;
            e.offset = (( instruction.arg >> 4 ) / 4 ) * 0x10 + ((instruction.arg & 0x0f));
            
            break;
        }
            
        case 0x98:
        case 0x99:
        case 0x9A:
        case 0x9B:
        {
            const std::unordered_map<int, int>instr = {{0x8, CBI}, {0x9, SBIC}, {0xA, SBI}, {0xB, SBIS}};
            std::runtime_error("IO not implemented yet!");
            break;
        }
            
        case 0x9C:
        {
            e.instruction_num = MUL;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x9D:
        {
            e.instruction_num = MUL;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x9E:
        {
            e.instruction_num = MUL;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x9F:
        {
            e.instruction_num = MUL;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
            
        case 0xA0:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 32;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xA1:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 32;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xA2:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 32;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xA3:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 32;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
            
        case 0xA4:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 40;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xA5:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 40;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xA6:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 40;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xA7:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 40;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
            
        case 0xA8:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 48;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xA9:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 48;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xAA:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 48;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xAB:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 48;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
            
        case 0xAC:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 56;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xAD:
        {
            e.instruction_num = LDD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 56;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xAE:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            e.offset = ( instruction.arg & 0x0f ) + 56;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
        case 0xAF:
        {
            e.instruction_num = STD;
            offset_1 = (((instruction.arg & 0xf0) >> 4) + 16);
            e.offset = ( instruction.arg & 0x0f ) + 56;
            
            if ( ( instruction.arg & 0x0f ) < 8 )
                offset_2 = REG_Z;
            else
                offset_2 = REG_Y;
            
            break;
        }
            
            
            // TODO: these cases can be rewritten in a smarter way, which I should probably do
            
        case 0x10:
        {
            e.instruction_num = CPSE;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x11:
        {
            e.instruction_num = CPSE;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x12:
        {
            e.instruction_num = CPSE;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x13:
        {
            e.instruction_num = CPSE;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
            
        case 0x14:
        {
            e.instruction_num = CP;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x15:
        {
            e.instruction_num = CP;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x16:
        {
            e.instruction_num = CP;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x17:
        {
            e.instruction_num = CP;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
            
        case 0x18:
        {
            e.instruction_num = SUB;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x19:
        {
            e.instruction_num = SUB;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x1A:
        {
            e.instruction_num = SUB;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x1B:
        {
            e.instruction_num = SUB;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
            
        case 0x20:
        {
            e.instruction_num = AND;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x21:
        {
            e.instruction_num = AND;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x22:
        {
            e.instruction_num = AND;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x23:
        {
            e.instruction_num = AND;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
            
        case 0x24:
        {
            e.instruction_num = EOR;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x25:
        {
            e.instruction_num = EOR;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x26:
        {
            e.instruction_num = EOR;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x27:
        {
            e.instruction_num = EOR;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x28:
        {
            e.instruction_num = OR;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x29:
        {
            e.instruction_num = OR;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x2A:
        {
            e.instruction_num = OR;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x2B:
        {
            e.instruction_num = OR;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x2C:
        {
            e.instruction_num = MOV;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x2D:
        {
            e.instruction_num = MOV;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0x2E:
        {
            e.instruction_num = MOV;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
        case 0x2F:
        {
            e.instruction_num = MOV;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f))  + 16;
            break;
        }
            
        case 0xF0:
        case 0xF1:
        {
            const std::unordered_map<int, int> cds = {{0, BRCS}, {1, BREQ}, {2, BRMI}, {4, BRVS}, {5, BRLT}, {6, BRHS}, {7, BRTS}, {8, BRIE}};
            e.instruction_num = cds.at((instruction.arg & 0xf0) / 2);
            if ( (instruction.arg & 0xf0) < 8 )
                e.offset = 4 * ((instruction.arg >> 4));
            else
                e.offset = 4 * ((instruction.arg >> 4)) + 2;
            break;
        }
        case 0xF2:
        case 0xF3:
        {
            const std::unordered_map<int, int> cds = {{0, BRCS}, {1, BREQ}, {2, BRMI}, {4, BRVS}, {5, BRLT}, {6, BRHS}, {7, BRTS}, {8, BRIE}};
            e.instruction_num = cds.at((instruction.arg & 0xf0) / 2);
            if ( (instruction.arg & 0xf0) < 8 )
                e.offset = - ( 128 - 4 * ((instruction.arg >> 4)));
            else
                e.offset = - ( 128 - 4 * ((instruction.arg >> 4))) + 2;
            break;
        }
            
        case 0xF4:
        case 0xF5:
        {
            const std::unordered_map<int, int> cds = {{0, BRCC}, {1, BRNE}, {2, BRPL}, {4, BRVC}, {5, BRGE}, {6, BRHC}, {7, BRTC}, {8, BRID}};
            e.instruction_num = cds.at((instruction.arg & 0xf0) / 2);
            if ( (instruction.arg & 0xf0) < 8 )
                e.offset = 4 * ((instruction.arg >> 4));
            else
                e.offset = 4 * ((instruction.arg >> 4)) + 2;
            break;
        }
        case 0xF6:
        case 0xF7:
        {
            const std::unordered_map<int, int> cds = {{0, BRCC}, {1, BRNE}, {2, BRPL}, {4, BRVC}, {5, BRGE}, {6, BRHC}, {7, BRTC}, {8, BRID}};
            e.instruction_num = cds.at((instruction.arg & 0xf0) / 2);
            if ( (instruction.arg & 0xf0) < 8 )
                e.offset = - ( 128 - 4 * ((instruction.arg >> 4)));
            else
                e.offset = - ( 128 - 4 * ((instruction.arg >> 4))) + 2;
            break;
        }
        case 0xF8:
        {
            e.instruction_num = BLD;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
            
        }
        case 0xF9:
        {
            e.instruction_num = BLD;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0xFA:
        {
            e.instruction_num = BST;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
            
        }
        case 0xFB:
        {
            e.instruction_num = BST;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0xFC:
        {
            e.instruction_num = SBRC;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
            
        }
        case 0xFD:
        {
            e.instruction_num = SBRC;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
        case 0xFE:
        {
            e.instruction_num = SBRS;
            offset_1 = (((instruction.arg & 0xf0) >> 4));
            offset_2 = ((instruction.arg & 0x0f));
            break;
            
        }
        case 0xFF:
        {
            e.instruction_num = SBRS;
            offset_1 = (((instruction.arg & 0xf0) >> 4)) + 16;
            offset_2 = ((instruction.arg & 0x0f));
            break;
        }
            
        default:
        {
            std::stringstream ss;
            ss << "0x" << std::hex << (int)instruction.opcode << (int)instruction.arg;
            
            std::cout << "Hits: " << CPU->progmem.size() << '\n';
            throw std::runtime_error("Instruction not implemented for decoding! " + ss.str());
        }
            
    }
    
    e.operand_1 = CPU->gp_registers + offset_1;
    e.operand_2 = CPU->gp_registers + offset_2;
    
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

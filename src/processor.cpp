#include "processor.hpp"

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

void Processor::execute(Executable e)
{
    switch ( e.instruction_num) {
        case PUSH:
        {
            SRAM[SP--] = *e.operand_1;
            PC++;
            break;
        }
        case RCALL:
        {
            SP -= 2;
            PC = PC + e.offset + 1;
        }
        case IN:
        {
            *e.operand_1 = SRAM[e.offset];
            PC++;
        }
            
        default:
            break;
    }
}

#pragma once

#include "fetcher.hpp"
#include "avr.hpp"
#include "processor.hpp"
#include "fetcher.hpp"

struct Decoder
{
    Processor* CPU;
    bool decode(const Instruction instruction);
    bool decodeRecord(Record r);
};
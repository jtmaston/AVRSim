#pragma once

#include <inttypes.h>
#include "processor.hpp"
#include "Executable.hpp"


struct Executer {
    struct Processor* processor;
    
    void execute(Executable e);
};

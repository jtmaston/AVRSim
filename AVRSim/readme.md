# What is this?

AVRSim is my latest trip into the low level area, by trying to recreate a complete AVR microprocessor in software, able to run binaries without the need to do any modifications.

# Goals
* Implement 80-90% of the AVR ISA in software. Having around 200 instructions, this isn't such a daunting task ( comparing to, say, x86 ), but still will take quite the brain power to even come close to being efficient.
* Variable execution speed ( pause execution on instruction, resume, simulate clock rate etc. )
* I/O mapping? Simulate input/output ports, like in an Arduino, for example.

# Road-map
* Initial work:
    - [] Implement the general architecture, in its simplest form, for which I have set the goal to have load, store, arithmetic and logic operations and a semi-functioning stack.
    - [] Implement more complex functions of the processor, such as port registers and I/O
    - [] Implement DMA ( direct memory access )
    - [] Implement interrupt support
    - [] Implement interfaces ( UART, SPI, I2C )
    - [] Implement timers
* Optimizations:
    * ???

* GUI
    * Implement a GUI.
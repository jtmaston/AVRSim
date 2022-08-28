//
//  avr.hpp
//  AVRSim
//
//  Created by Alex ANASTASIU on 8/4/22.
//  The AVR Instruction Set, AVR bradning are copyright (c) Microchip Technology Inc.
//  This file is meant to be a human readable define to number, for the AVR interpreter.
//  No claims of ownership are made to the instructions defined by the ISA.

#pragma once

enum ISA
{
    ADD,
    ADC,
    ADIW,
    SUB,
    SUBI,
    SBC,
    SBCI,
    SBIW,
    AND,
    ANDI,
    OR,
    ORI,
    EOR,
    COM,
    NEG,
    SBR,
    CBR,
    INC,
    DEC,
    TST,
    CLR,
    SER,
    MUL,
    MULS,
    MULSU,
    FMUL,
    FMULS,
    FMULSU,
    DES,
    RJMP,
    IJMP,
    EIJMP,
    JMP,
    RCALL,
    ICALL,
    EICALL,
    CALL,
    RET,
    RETI,
    CPSE,
    CP,
    CPC,
    CPI,
    SBRC,
    SBRS,
    SBIC,
    SBIS,
    BRBS,
    BRBC,
    BREQ,
    BRNE,
    BRCS,
    BRCC,
    BRSH,
    BRLO,
    BRMI,
    BRPL,
    BRGE,
    BRLT,
    BRHS,
    BRHC,
    BRTS,
    BRTC,
    BRVS,
    BRVC,
    BRIE,
    BRID,
    MOV,
    MOVW,
    LDI,
    LDS,
    LD, // TODO: invesigate
    /*LD
    LD
    LD
    LD
    LD
    LDD
    LD
    LD*/
    ID,
    LDD,
    STS,
    ST,
    /*ST
    ST
    ST
    ST
    ST
    STD
    ST
    ST
    ST*/
    STD,
    LPM,
    // LPM
    // LPM
    ELPM,
    // ELPM
    // ELPM
    SPM,
    // SPM
    IN,
    OUT,
    PUSH,
    POP,
    XCH,
    LAS,
    LAC,
    LAT,
    LSL,
    LSR,
    ROL,
    ROR,
    ASR,
    SWAP,
    SBI,
    CBI,
    BST,
    BLD,
    BSET,
    BCLR,
    SEC,
    CLC,
    SEN,
    CLN,
    SEZ,
    CLZ,
    SEI,
    CLI,
    SES,
    CLS,
    SEV,
    CLV,
    SET,
    CLT,
    SEH,
    CLH,
    BREAK,
    NOP,
    SLEEP,
    WDR,
};

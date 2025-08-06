#ifndef OPCODE_H_
#define OPCODE_H_

#include <string.h>

typedef enum {
    ADC, AND, ASL, BCC, BCS, BEQ, BIT,
    BMI, BNE, BPL, BRK, BVC, BVS, CLC,
    CLD, CLI, CLV, CMP, CPX, CPY, DEC,
    DEX, DEY, EOR, INC, INX, INY, JMP,
    JSR, LDA, LDX, LDY, LSR, NOP, ORA,
    PHA, PHP, PLA, PLP, ROL, ROR, RTI,
    RTS, SBC, SEC, SED, SEI, STA, STX,
    STY, TAX, TAY, TSX, TXA, TXS, TYA,
    INSTRUCTION_COUNT,
} InstructionKind;

const char *instr_kind_to_str(InstructionKind kind);
InstructionKind str_to_instr_kind(const char *str);

#endif // OPCODE_H_

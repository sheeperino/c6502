#include "opcode.h"

const char *str_instructions[] = {
  "ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT",
  "BMI", "BNE", "BPL", "BRK", "BVC", "BVS", "CLC",
  "CLD", "CLI", "CLV", "CMP", "CPX", "CPY", "DEC",
  "DEX", "DEY", "EOR", "INC", "INX", "INY", "JMP",
  "JSR", "LDA", "LDX", "LDY", "LSR", "NOP", "ORA",
  "PHA", "PHP", "PLA", "PLP", "ROL", "ROR", "RTI",
  "RTS", "SBC", "SEC", "SED", "SEI", "STA", "STX",
  "STY", "TAX", "TAY", "TSX", "TXA", "TXS", "TYA",
};

const char *instr_kind_to_str(InstructionKind kind) {
  return (kind == INSTRUCTION_COUNT
          ? "invalid" : str_instructions[kind]);
}

InstructionKind str_to_instr_kind(const char *str) {
  if      (strncasecmp("ADC", str, 3) == 0) return ADC;
  else if (strncasecmp("AND", str, 3) == 0) return AND;
  else if (strncasecmp("ASL", str, 3) == 0) return ASL;
  else if (strncasecmp("BCC", str, 3) == 0) return BCC;
  else if (strncasecmp("BCS", str, 3) == 0) return BCS;
  else if (strncasecmp("BEQ", str, 3) == 0) return BEQ;
  else if (strncasecmp("BIT", str, 3) == 0) return BIT;
  else if (strncasecmp("BMI", str, 3) == 0) return BMI;
  else if (strncasecmp("BNE", str, 3) == 0) return BNE;
  else if (strncasecmp("BPL", str, 3) == 0) return BPL;
  else if (strncasecmp("BRK", str, 3) == 0) return BRK;
  else if (strncasecmp("BVC", str, 3) == 0) return BVC;
  else if (strncasecmp("BVS", str, 3) == 0) return BVS;
  else if (strncasecmp("CLC", str, 3) == 0) return CLC;
  else if (strncasecmp("CLD", str, 3) == 0) return CLD;
  else if (strncasecmp("CLI", str, 3) == 0) return CLI;
  else if (strncasecmp("CLV", str, 3) == 0) return CLV;
  else if (strncasecmp("CMP", str, 3) == 0) return CMP;
  else if (strncasecmp("CPX", str, 3) == 0) return CPX;
  else if (strncasecmp("CPY", str, 3) == 0) return CPY;
  else if (strncasecmp("DEC", str, 3) == 0) return DEC;
  else if (strncasecmp("DEX", str, 3) == 0) return DEX;
  else if (strncasecmp("DEY", str, 3) == 0) return DEY;
  else if (strncasecmp("EOR", str, 3) == 0) return EOR;
  else if (strncasecmp("INC", str, 3) == 0) return INC;
  else if (strncasecmp("INX", str, 3) == 0) return INX;
  else if (strncasecmp("INY", str, 3) == 0) return INY;
  else if (strncasecmp("JMP", str, 3) == 0) return JMP;
  else if (strncasecmp("JSR", str, 3) == 0) return JSR;
  else if (strncasecmp("LDA", str, 3) == 0) return LDA;
  else if (strncasecmp("LDX", str, 3) == 0) return LDX;
  else if (strncasecmp("LDY", str, 3) == 0) return LDY;
  else if (strncasecmp("LSR", str, 3) == 0) return LSR;
  else if (strncasecmp("NOP", str, 3) == 0) return NOP;
  else if (strncasecmp("ORA", str, 3) == 0) return ORA;
  else if (strncasecmp("PHA", str, 3) == 0) return PHA;
  else if (strncasecmp("PHP", str, 3) == 0) return PHP;
  else if (strncasecmp("PLA", str, 3) == 0) return PLA;
  else if (strncasecmp("PLP", str, 3) == 0) return PLP;
  else if (strncasecmp("ROL", str, 3) == 0) return ROL;
  else if (strncasecmp("ROR", str, 3) == 0) return ROR;
  else if (strncasecmp("RTI", str, 3) == 0) return RTI;
  else if (strncasecmp("RTS", str, 3) == 0) return RTS;
  else if (strncasecmp("SBC", str, 3) == 0) return SBC;
  else if (strncasecmp("SEC", str, 3) == 0) return SEC;
  else if (strncasecmp("SED", str, 3) == 0) return SED;
  else if (strncasecmp("SEI", str, 3) == 0) return SEI;
  else if (strncasecmp("STA", str, 3) == 0) return STA;
  else if (strncasecmp("STX", str, 3) == 0) return STX;
  else if (strncasecmp("STY", str, 3) == 0) return STY;
  else if (strncasecmp("TAX", str, 3) == 0) return TAX;
  else if (strncasecmp("TAY", str, 3) == 0) return TAY;
  else if (strncasecmp("TSX", str, 3) == 0) return TSX;
  else if (strncasecmp("TXA", str, 3) == 0) return TXA;
  else if (strncasecmp("TXS", str, 3) == 0) return TXS;
  else if (strncasecmp("TYA", str, 3) == 0) return TYA;
  return INSTRUCTION_COUNT;
}

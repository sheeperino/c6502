#ifndef LEXER_H_
#define LEXER_H_

#include "opcode.h"
#include <stddef.h>

#define PROGRAM_SIZE 4096
#define str_token(k, c) ((Token){.kind = (k), .content = (c)})
#define num_token(k, v) ((Token){.kind = (k), .value = (v)})
#define token(k) ((Token){.kind = (k)})

typedef enum {
  TOK_INSTRUCTION,
  TOK_IDENTIFIER,

  TOK_NUM_SHORT,
  TOK_NUM_LONG,

  // Registers
  TOK_A,
  TOK_X,
  TOK_Y,

  // Aliases (alias = ADDR)
  TOK_EQUAL,

  // Labels (label:)
  TOK_COLON,

  // Indexed (eg. ADDR,x)
  TOK_COMMA,

  // Indirect
  TOK_LPAREN,
  TOK_RPAREN,

  // Number base
  TOK_DOLLAR,
  TOK_PERCENT,

  // Direct mode
  TOK_HASH,

  TOK_NEWLINE,
  TOK_END,
} TokenKind;

typedef struct {
  TokenKind kind;
  union {
    struct { const char *content; size_t len; }; // string
    int value; // number / instruction
  };
} Token;

const char *token_name(TokenKind kind);

typedef struct {
  size_t pos, len;
  size_t tok_cur;
  const char *data;
  int error;

  Token tokens[PROGRAM_SIZE];
} Lexer;

Lexer create_lexer(const char *code);
// Single character token
void add_token(Lexer *l, TokenKind kind);
// Multi character token
void add_string(Lexer *l, TokenKind kind, const char *content, size_t len);
void add_instr(Lexer *l, InstructionKind instr);
void add_number(Lexer *l, int base);
void scan(Lexer *l);

#endif // LEXER_H_

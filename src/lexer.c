#define NOB_IMPLEMENTATION
#include "../nob.h"

#include "lexer.h"
#include <assert.h>
#include <ctype.h>
#include <string.h>

Lexer create_lexer(const char *code) {
  Lexer l;
  l.error = 0;
  l.pos = 0;
  l.data = code;
  l.len = strlen(code);
  l.tok_cur = 0;
  return l;
}

void add_token(Lexer *l, TokenKind kind) {
  Token tok;
  tok.kind = kind;
  tok.content = NULL;
  l->pos++;
  l->tokens[l->tok_cur++] = tok;
}

void add_string(Lexer *l, TokenKind kind, const char *content, size_t len) {
  Token tok;
  tok.kind = kind;
  tok.content = content;
  tok.len = len;
  l->tokens[l->tok_cur++] = tok;
}

void add_instr(Lexer *l, InstructionKind instr) {
  Token tok;
  tok.kind = TOK_INSTRUCTION;
  tok.value = instr;
  l->tokens[l->tok_cur++] = tok;
}

static int is_token_end(char c) {
  switch (c) {
    case ' ': case '\t': case '\n': case '\r':
    case '\0': case ',': case '(': case ')':
      return 1;
  }
  return 0;
}

static int isbdigit(int c) { return (c == '0' || c == '1'); }
static int parse_num(int val, char c, int base) {
  assert((base == 2 || base == 10 || base == 16) && "Invalid number base");
  if (base == 2) return val * 2 + c - '0';
  else if (base == 10) return val * 10 + c - '0';
  else return val * 16 + (c & 15) + (c >= 'A' ? 9 : 0);
}

void add_number(Lexer *l, int base) {
  assert((base == 2 || base == 10 || base == 16) && "Invalid number base");
  Token tok;
  int (*f)(int);
  char c;
  int val = 0, i = 0;

  if (base == 2) f = isbdigit;
  else if (base == 10) f = isdigit;
  else f = isxdigit;

  for (;;) {
    c = l->data[++l->pos];
    if ((f)(c)) {
      val = parse_num(val, c, base);
    }
    else if (is_token_end(c)) break;
    else {
      l->error = 1;
      break;
    }
    i++;
  }
  if (i == 0 || val > 65535) l->error = 1;

  tok.kind = (val > 255 ? TOK_NUM_LONG : TOK_NUM_SHORT);
  tok.value = val;
  l->tokens[l->tok_cur++] = tok;
}

static void next_token(Lexer *l) {
  char c = l->data[l->pos];

  if (c == '\n' || c == '\r') add_token(l, TOK_NEWLINE);
  else if (c == ' ' || c == '\t') l->pos++;
  else if (c == '=') add_token(l, TOK_EQUAL);
  else if (c == ':') add_token(l, TOK_COLON);
  else if (c == ',') add_token(l, TOK_COMMA);
  else if (c == '(') add_token(l, TOK_LPAREN);
  else if (c == ')') add_token(l, TOK_RPAREN);
  else if (c == '#') add_token(l, TOK_HASH);
  else if (c == ';') { // skip comments
    while (((c = l->data[++l->pos]) != '\n' || c == '\r') && l->pos < l->len);
  }
  else if (c == '%') { // binary number literal
    add_number(l, 2);
  }
  else if (c >= '0' && c <= '9') { // decimal number literal
    l->pos--;
    add_number(l, 10);
  }
  else if (c == '$') { // hex number literal
    add_number(l, 16);
  }
  else if (isalpha(c) || c == '_') { // identifiers
    size_t len = 1;
    while ((c = l->data[++l->pos]) == '_' || isalnum(c)) {
      len++;
    }

    const char *text = l->data + l->pos - len;
    if (len == 1) { // check if register
      if (*text == 'a' || *text == 'A') {
        add_token(l, TOK_A);
        return;
      } else if (*text == 'x' || *text == 'X') {
        add_token(l, TOK_X);
        return;
      } else if (*text == 'y' || *text == 'Y') {
        add_token(l, TOK_Y);
        return;
      }
    }
    else if (len == 3) { // all instructions are 3 bytes long
      InstructionKind instr = str_to_instr_kind(text);
      if (instr != INSTRUCTION_COUNT) {
        add_instr(l, instr);
        return;
      }
    }
    add_string(l, TOK_IDENTIFIER, text, len);
  }
  else { // unknown character
    l->error = 1;
    l->pos++;
  }
}

const char *token_name(TokenKind kind) {
  switch (kind) {
    case TOK_INSTRUCTION: return "instruction";
    case TOK_IDENTIFIER: return "identifier";
    case TOK_NUM_SHORT: return "short number";
    case TOK_NUM_LONG: return "long number";
    case TOK_A: return "A register";
    case TOK_X: return "X register";
    case TOK_Y: return "Y register";
    case TOK_EQUAL: return "equal";
    case TOK_COLON: return "colon";
    case TOK_COMMA: return "comma";
    case TOK_LPAREN: return "open paren";
    case TOK_RPAREN: return "close paren";
    case TOK_DOLLAR: return "dollar sign";
    case TOK_PERCENT: return "percent";
    case TOK_HASH: return "hash";
    case TOK_NEWLINE: return "newline";
    case TOK_END: return "end token";
  }
  NOB_UNREACHABLE("All TokenKind's should be handled.");
}

void scan(Lexer *l) {
  while (l->pos < l->len) {
    next_token(l);
  }
  l->tokens[l->tok_cur].kind = TOK_END;
}

#include "../src/lexer.h"
#include "../src/opcode.h"
#include <stdio.h>

#define TESTS_BEGIN(suite_name)\
  do {\
    test_count = 0;\
    passed_count = 0;\
    printf("\n(Running %s tests...)\n", suite_name);\
  } while (0)

#define TESTS_END()\
  printf("Done. %zu out of %zu tests passed.\n\n", passed_count, test_count)

#define cmp(name, code, ...)\
  do {\
    Token arr[] = {__VA_ARGS__, token(TOK_END)};\
    test_tokens = arr;\
    _cmp(name, code, test_tokens);\
  } while (0)

#define RESET "\e[0m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"

#define pass_print(fmt, ...)\
  printf("%s" "PASS " fmt "%s", GREEN, __VA_ARGS__, RESET)
#define fail_print(fmt, ...)\
  printf("%s" "FAIL " fmt "%s", RED, __VA_ARGS__, RESET)

static size_t test_count;
static size_t passed_count;
static Token *test_tokens;

void should_fail(const char *name, const char *code) {
  test_count++;
  Lexer lexer = create_lexer(code);
  scan(&lexer);

  if (lexer.error) {
    pass_print("%s\n", name);
    passed_count++;
  } else {
    fail_print("%s\n", name);
  }
}

static int _tok_cmp(const char *name, Token *t1, Token *t2) {
  if (t1->kind != t2->kind) {
    fail_print("%s - mismatched kinds (%s) vs (%s)\n",
      name, token_name(t1->kind), token_name(t2->kind)
    );
    return 0;
  } else if (t2->kind == TOK_IDENTIFIER) {
    if (strncmp(t1->content, t2->content, t1->len) != 0) {
      fail_print("%s - mismatched contents '%.*s' vs '%s'\n",
        name, (int)t1->len, t1->content, t2->content
      );
      return 0;
    }
  } else if (t2->kind == TOK_INSTRUCTION) {
    if (t1->value != t2->value) {
      fail_print("%s - mismatched instructions %s vs %s\n",
        name, instr_kind_to_str(t1->value), instr_kind_to_str(t2->value)
      );
      return 0;
    }
  } else if (t2->kind == TOK_NUM_SHORT || t2->kind == TOK_NUM_LONG) {
    if (t1->value != t2->value) {
      fail_print("%s - mismatched contents %d vs %d\n",
        name, t1->value, t2->value
      );
      return 0;
    }
  }
  return 1;
}

static void _cmp(const char *name, const char *code, Token *tokens) {
  test_count++;
  Lexer lexer = create_lexer(code);
  scan(&lexer);
  int i = 0;
  Token t1, t2;
  while ((t1 = lexer.tokens[i]).kind != TOK_END
  &&     (t2 = tokens[i]).kind != TOK_END)
  {
    if (_tok_cmp(name, &t1, &t2) == 0) return;
    i++;
  }

  if (i != (int)lexer.tok_cur) {
    fail_print("%s - mismatched token count (%zu vs %d)\n", name, lexer.tok_cur, i);
    return;
  }
  if (lexer.error) {
    fail_print("%s - lexer error\n", name);
    return;
  }
  pass_print("%s\n", name);
  passed_count++;
}

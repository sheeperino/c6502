#include "util.c"
int main() {
TESTS_BEGIN("lexer");
  cmp("short hex", "$FF", num_token(TOK_NUM_SHORT, 0xFF));
  cmp("long hex", "$FFFF", num_token(TOK_NUM_LONG, 0xFFFF));
  should_fail("too long hex", "$12345");
  should_fail("malformed hex", "$EFG");
  should_fail("empty hex", "$");

  cmp("short bin", "%11111111", num_token(TOK_NUM_SHORT, 0b11111111));
  cmp("long bin", "%1111111111111111", num_token(TOK_NUM_LONG, 0b1111111111111111));
  should_fail("too long bin", "%101010101010101010");
  should_fail("malformed bin", "%012");
  should_fail("empty bin", "%");

  cmp("short dec", "255", num_token(TOK_NUM_SHORT, 255));
  cmp("long dec", "65535", num_token(TOK_NUM_LONG, 65535));
  should_fail("too long dec", "1234567890");
  should_fail("malformed dec", "1A");

  cmp("A register", "ASL A", num_token(TOK_INSTRUCTION, ASL), token(TOK_A));
  cmp("X register", "sta $00,X",
    num_token(TOK_INSTRUCTION, STA),
    num_token(TOK_NUM_SHORT, 0x00),
    token(TOK_COMMA),
    token(TOK_X)
  );
  cmp("Y register", "STA $4000, Y",
    num_token(TOK_INSTRUCTION, STA),
    num_token(TOK_NUM_LONG, 0x4000),
    token(TOK_COMMA),
    token(TOK_Y)
  );

  cmp("indentifier", "meow", str_token(TOK_IDENTIFIER, "meow"));

  cmp("comments", ";this is a comment\t\nbark;this is another comment\nmeow",
    token(TOK_NEWLINE),
    str_token(TOK_IDENTIFIER, "bark"),
    token(TOK_NEWLINE),
    str_token(TOK_IDENTIFIER, "meow")
  );

  cmp("whitespaces", "\tSTA $123\n asl \r\n",
    num_token(TOK_INSTRUCTION, STA),
    num_token(TOK_NUM_LONG, 0x123),
    token(TOK_NEWLINE),
    num_token(TOK_INSTRUCTION, ASL),
    token(TOK_NEWLINE),
    token(TOK_NEWLINE)
  );

  cmp("valid characters", "(),:=#",
    token(TOK_LPAREN),
    token(TOK_RPAREN),
    token(TOK_COMMA),
    token(TOK_COLON),
    token(TOK_EQUAL),
    token(TOK_HASH)
  );

  should_fail("invalid characters", "~@");
TESTS_END();
}

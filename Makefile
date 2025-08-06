all:
	$(CC) src/c6502.c src/lexer.c src/opcode.c -o build/c6502

run_tests:
	$(CC) test/tests.c src/lexer.c src/opcode.c -o tests && ./tests
	@-rm tests

#define NOB_IMPLEMENTATION
#include "nob.h"

#define BUILD_FOLDER "build/"
#define TESTS_FOLDER "test/"

#define SOURCES "src/lexer.c", "src/opcode.c"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  nob_shift(argv, argc);

  if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

  Nob_Cmd cmd = {0};
  const char *cmd_name;

  nob_cc(&cmd);
  nob_cc_flags(&cmd);
  nob_cc_inputs(&cmd, SOURCES);

  if (argc > 0) {
    cmd_name = nob_shift(argv, argc);
  } else {
    nob_cmd_append(&cmd, "src/c6502.c");
    nob_cc_output(&cmd, BUILD_FOLDER "c6502");
    if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;
    return 0;
  }

  if (strcmp(cmd_name, "test") == 0) {
    nob_cmd_append(&cmd, "test/tests.c");
    nob_cc_output(&cmd, BUILD_FOLDER "tests");
    if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;
    nob_cmd_append(&cmd, BUILD_FOLDER "tests");
    return !nob_cmd_run_sync_and_reset(&cmd);
  }

  nob_log(NOB_ERROR, "Unknown command: %s", cmd_name);

  return 0;
}

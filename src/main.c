#include "command.h"
#include "storage.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *command;
  if (argc < 2) {
    command = "help";
  } else {
    command = argv[1];
  }

  enum CommandType command_type = get_command_type(command);

  if (command_type == COMMAND_TYPE_HELP) {
    print_help();
  }

  Storage s = storage_create("storage.txt");
  storage_load(s);

  printf("%s", (char *)vector_get(storage_lines(s), 0));

  return 0;
}

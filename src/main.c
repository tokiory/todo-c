#include "command.h"
#include "storage.h"
#include "todo.h"

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

  Todo todo = todo_create();
  todo = todo_fill(todo, s);

  return 0;
}

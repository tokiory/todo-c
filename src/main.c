#include "adapter.h"
#include "command.h"
#include "todo.h"
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

  Storage s = storage_create("storage.txt");
  storage_load(s);

  Todo todo = todo_create();
  storage_to_todo(s, todo);

  switch (command_type) {
  case COMMAND_TYPE_HELP:
    print_help();
    break;
  case COMMAND_TYPE_CREATE:
    if (argc < 3) {
      printf("Usage: %s add <title>\n", argv[0]);
      return 1;
    }
    todo_create_item(todo, argv[2]);
    printf("Task created successfully\n");
    break;
  case COMMAND_TYPE_LIST:
    todo_list_items(todo);
    break;
  case COMMAND_TYPE_DELETE:
    if (argc < 3) {
      printf("Usage: %s del <task_id>\n", argv[0]);
      return 1;
    }
    todo_delete_item(todo, argv[2]);
    printf("Task deleted successfully\n");
    break;
  case COMMAND_TYPE_UPDATE:
    if (argc < 4) {
      printf("Usage: %s upd <task_id> <new_title>\n", argv[0]);
      return 1;
    }
    todo_update_item(todo, argv[2], argv[3], false);
    printf("Task updated successfully\n");
    break;
  case COMMAND_TYPE_DONE:
    if (argc < 3) {
      printf("Usage: %s done <task_id>\n", argv[0]);
      return 1;
    }
    todo_mark_done(todo, argv[2]);
    printf("Task marked as done\n");
    break;
  case COMMAND_TYPE_UNKNOWN:
  default:
    if (command) {
      printf("Command %s not exists. Type -h to see help message\n", command);
      return 1;
    }
    print_help();
  }

  todo_to_storage(todo, s);
  storage_write(s);
  return 0;
}

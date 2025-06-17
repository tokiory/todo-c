#include "command.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

bool _is_command(const char *variants[], size_t var_length,
                 const char *command) {
  for (int i = 0; i < var_length; i++) {
    if (strcmp(variants[i], command) == 0) {
      return true;
    }
  }

  return false;
}

bool _is_command_help(const char *command) {
  return _is_command((const char *[]){"help", "h", "-h", "--help"}, 4, command);
}

bool _is_command_add(const char *command) {
  return _is_command((const char *[]){"add", "a", "-a", "--add"}, 4, command);
}

bool _is_command_del(const char *command) {
  return _is_command((const char *[]){"del", "d", "-d", "--del"}, 4, command);
}

bool _is_command_list(const char *command) {
  return _is_command((const char *[]){"ls", "--list", "-l"}, 3, command);
}

bool _is_command_done(const char *command) {
  return _is_command((const char *[]){"done", "do", "--do", "--done"}, 4, command);
}



bool _is_command_upd(const char *command) {
  return _is_command((const char *[]){"upd", "u", "--update", "-u"}, 4,
                     command);
}

enum CommandType get_command_type(const char *command) {
  if (_is_command_help(command)) {
    return COMMAND_TYPE_HELP;
  }

  if (_is_command_done(command)) {
    return COMMAND_TYPE_DONE;
  }

  if (_is_command_list(command)) {
    return COMMAND_TYPE_LIST;
  }

  if (_is_command_add(command)) {
    return COMMAND_TYPE_CREATE;
  }

  if (_is_command_del(command)) {
    return COMMAND_TYPE_DELETE;
  }

  if (_is_command_upd(command)) {
    return COMMAND_TYPE_UPDATE;
  }

  return COMMAND_TYPE_UNKNOWN;
}

void print_help() {
  printf("Usage: todo-c [COMMAND] [ARGS]\n");
  printf("Commands:\n");
  printf("\thelp, h, -h, --help:\tPrints this help message\n");
  printf("\tadd, a, -a, --add:\tAdds a new task\n");
  printf("\tdel, d, -d, --del:\tDeletes a task\n");
  printf("\tls, --list, -l:\t\tLists all tasks\n");
  printf("\tupd, u, --update, -u:\tUpdates a task\n");
  printf("\tdone, do, --done:\tMarks a task as done\n");
}

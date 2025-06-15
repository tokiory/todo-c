enum CommandType {
  COMMAND_TYPE_UNKNOWN,
  COMMAND_TYPE_HELP,
  COMMAND_TYPE_CREATE,
  COMMAND_TYPE_LIST,
  COMMAND_TYPE_UPDATE,
  COMMAND_TYPE_DELETE
};


enum CommandType get_command_type(const char *command);
void print_help();

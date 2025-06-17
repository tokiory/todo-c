#include "hashmap.h"
#include "storage.h"
#include <stdbool.h>

#ifndef TODO_H
#define TODO_H

struct TodoTask {
  char *id;
  char *title;
  bool is_done;
};

struct Todo {
  Hashmap tasks;
};

typedef struct TodoTask *TodoTask;
typedef struct Todo *Todo;

Todo todo_create();
void todo_destroy(Todo todo);
void todo_delete_item(Todo t, char *id);
void todo_update_item(Todo t, char *id, char *title, bool is_done);
void todo_create_item(Todo t, char *title);
void todo_mark_done(Todo t, char *id);
void todo_list_items(Todo t);
#endif

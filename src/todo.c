#include "hashmap.h"
#include "todo.h"
#include "storage.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TodoTask {
  char *id;
  char *title;
  bool is_done;
};

struct Todo {
  Hashmap tasks;
};

Todo todo_create() {
  Todo todo = malloc(sizeof(struct Todo));
  todo->tasks = hashmap_create();
  return todo;
}

Todo todo_fill(Todo t, Storage s) {
  Vector raw_tasks = storage_lines(s);
  for (int i = 0; i < vector_size(raw_tasks); i++) {
    char *raw_task = vector_get(raw_tasks, i);

    unsigned field_idx = 0;
    char *raw_fields[3] = {NULL, NULL, NULL};
    char *files = strtok(strdup(raw_task), "\t");

    while (files != NULL && field_idx < 3) {
      raw_fields[field_idx++] = files;
      files = strtok(NULL, "\t");
    }

    if (field_idx < 3) {
      perror("Invalid task format");
      free(raw_task);
      continue;
    }

    TodoTask task = malloc(sizeof(struct TodoTask));
    char *id = raw_fields[0];
    task->id = id;
    task->title = strdup(raw_fields[1]);
    task->is_done = strcmp(raw_fields[2], "1") == 0;
    hashmap_set(t->tasks, id, task);
  }

  return t;
}

void todo_destroy(Todo todo) {
  hashmap_destroy(todo->tasks);
  free(todo);
}

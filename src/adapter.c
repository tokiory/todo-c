#include "storage.h"
#include "todo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void storage_to_todo(Storage s, Todo t) {
  Vector raw_tasks = storage_lines(s);
  for (int i = 0; i < vector_size(raw_tasks); i++) {
    char *raw_task = (char*)vector_get(raw_tasks, i);
    if (raw_task == NULL) continue;

    unsigned field_idx = 0;
    char *raw_fields[3] = {NULL, NULL, NULL};
    char *task_copy = strdup(raw_task);
    char *files = strtok(task_copy, "\t");

    while (files != NULL && field_idx < 3) {
      raw_fields[field_idx++] = files;
      files = strtok(NULL, "\t");
    }

    if (field_idx < 3) {
      perror("Invalid task format");
      free(task_copy);
      continue;
    }

    TodoTask task = malloc(sizeof(struct TodoTask));
    task->id = strdup(raw_fields[0]);
    task->title = strdup(raw_fields[1]);
    task->is_done = strcmp(raw_fields[2], "1") == 0;
    hashmap_set(t->tasks, task->id, task);
    free(task_copy);
  }
}

void todo_to_storage(Todo t, Storage s) {
  Vector tasks = hashmap_entries(t->tasks);
  Vector lines = vector_create(sizeof(char*));
  printf("DEBUG: Found %lu tasks\n", vector_size(tasks));
  for (int i = 0; i < vector_size(tasks); i++) {
    TodoTask *task_ptr = vector_get(tasks, i);
    if (task_ptr == NULL) continue;
    TodoTask task = *task_ptr;
    char *id = task->id;
    char *title = task->title;
    char *status = task->is_done ? "1" : "0";
    printf("DEBUG: Task ID: '%s', Title: '%s', Status: '%s'\n", id, title, status);
    char *line = malloc(strlen(id) + strlen(title) + strlen(status) + 3);
    sprintf(line, "%s\t%s\t%s", id, title, status);
    printf("DEBUG: Line: '%s'\n", line);
    vector_push(lines, line);
  }

  storage_rewrite(s, lines);
}

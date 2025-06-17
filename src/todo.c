#include "todo.h"
#include "storage.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>

Todo todo_create() {
  Todo todo = malloc(sizeof(struct Todo));
  todo->tasks = hashmap_create();
  return todo;
}

void todo_destroy(Todo todo) {
  hashmap_destroy(todo->tasks);
  free(todo);
}

void todo_create_item(Todo t, char *title) {
  uuid_t uuid;
  uuid_generate(uuid);

  TodoTask task = malloc(sizeof(struct TodoTask));
  task->title = strdup(title);
  task->is_done = false;
  task->id = malloc(37); // UUID string is 36 chars + null terminator
  uuid_unparse(uuid, task->id);
  hashmap_set(t->tasks, task->id, task);
}

void todo_update_item(Todo t, char *id, char *title, bool is_done) {
  TodoTask task = hashmap_get(t->tasks, id);
  if (task == NULL) {
    printf("Task with ID '%s' not found\n", id);
    return;
  }
  free(task->title);
  task->title = strdup(title);
  task->is_done = is_done;
  hashmap_set(t->tasks, task->id, task);
}

void todo_delete_item(Todo t, char *id) {
  TodoTask task = hashmap_get(t->tasks, id);
  if (task == NULL) {
    printf("Task with ID '%s' not found\n", id);
    return;
  }
  hashmap_del(t->tasks, id);
  free(task->id);
  free(task->title);
  free(task);
}

void todo_mark_done(Todo t, char *id) {
  TodoTask task = hashmap_get(t->tasks, id);
  if (task == NULL) {
    printf("Task with ID '%s' not found\n", id);
    return;
  }
  task->is_done = true;
  hashmap_set(t->tasks, task->id, task);
}

void todo_list_items(Todo t) {
  Vector tasks = hashmap_entries(t->tasks);
  size_t count = vector_size(tasks);
  
  if (count == 0) {
    printf("No tasks found.\n");
    return;
  }
  
  printf("Tasks:\n");
  for (size_t i = 0; i < count; i++) {
    TodoTask *task_ptr = vector_get(tasks, i);
    if (task_ptr == NULL) continue;
    TodoTask task = *task_ptr;
    
    const char *status = task->is_done ? "[x]" : "[ ]";
    printf("%s %s (ID: %s)\n", status, task->title, task->id);
  }
}

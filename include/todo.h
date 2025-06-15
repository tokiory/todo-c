#include "storage.h"

struct TodoTask;
struct Todo;
typedef struct TodoTask *TodoTask;
typedef struct Todo *Todo;

Todo todo_create();
Todo todo_fill(Todo t, Storage s);
void todo_destroy(Todo todo);

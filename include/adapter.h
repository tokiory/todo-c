#include "storage.h"
#include "todo.h"

#ifndef ADAPTER_H
#define ADAPTER_H
  void storage_to_todo(Storage s, Todo t);
  void todo_to_storage(Todo t, Storage s);
#endif

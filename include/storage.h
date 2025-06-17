#include "vector.h"

#ifndef STORAGE_H
#define STORAGE_H

struct Storage;
typedef struct Storage *Storage;

Storage storage_create(const char* path);
void storage_load(Storage s);
void storage_write(Storage s);
void storage_rewrite(Storage s, Vector lines);
Vector storage_lines(Storage s);
void storage_destroy(Storage s);

#endif

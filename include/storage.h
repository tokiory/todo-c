#include "vector.h"

struct Storage;
typedef struct Storage *Storage;

Storage storage_create(const char* path);
void storage_load(Storage s);
void storage_write(Storage s);
Vector storage_lines(Storage s);
void storage_destroy(Storage s);

#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STORAGE_DEFAULT_PATH "storage.txt"

struct Storage {
  const char *path;
  Vector lines;
};

Storage storage_create(const char *path) {
  Storage s = malloc(sizeof(Storage));
  s->path = path ? path : STORAGE_DEFAULT_PATH;
  s->lines = vector_create(sizeof(char *));

  return s;
}

FILE *storage_file(Storage s) {
  FILE *f = fopen(s->path, "r");

  if (f == NULL) {
    printf("Can't load the storage, so we're creating a new one\n");
    f = fopen(s->path, "w");
    return f;
  }

  return f;
}

void storage_load(Storage s) {
  FILE *f = storage_file(s);

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, f)) != -1) {
    if (line[read-1] == '\n') {
      line[read-1] = '\0';
    }

    vector_push(s->lines, strdup(line));
  }

  free(line);
  fclose(f);
}

void storage_write(Storage s) {};

Vector storage_lines(Storage s) { return s->lines; }

void storage_destroy(Storage s);

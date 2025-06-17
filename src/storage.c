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

void storage_rewrite(Storage s, Vector lines) {
  s->lines = lines;
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

    char *line_copy = strdup(line);
    vector_push(s->lines, line_copy);
  }

  free(line);
  fclose(f);
}

void storage_write(Storage s) {
FILE *f = fopen(s->path, "w");

  if (f == NULL) {
    printf("Error: Could not open file for writing\n");
    return;
  }

  size_t count = vector_size(s->lines);
  printf("DEBUG: storage_write - writing %zu lines\n", count);
  for (size_t i = 0; i < count; i++) {
    char *line = (char*)vector_get(s->lines, i);
    if (line == NULL) continue;
    printf("DEBUG: storage_write - line: '%s'\n", line);
    fprintf(f, "%s\n", line);
  }

  fclose(f);
}

Vector storage_lines(Storage s) { return s->lines; }

void storage_destroy(Storage s);

#include <stdlib.h>

#ifndef VECTOR_H
#define VECTOR_H

  struct Vector;
  typedef struct Vector *Vector;

  Vector vector_create(size_t datasize);
  void vector_destroy(Vector v);
  void *vector_push(Vector v, void *value);
  void *vector_pop(Vector v);
  unsigned long vector_size(Vector v);
  unsigned long vector_capacity(Vector v);
  void *vector_get(Vector v, unsigned long index);

#endif

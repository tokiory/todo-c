#include <stdint.h>
#include <stdlib.h>

#define VECTOR_INITIAL_CAPACITY 16

struct Vector {
  unsigned long _capacity;
  unsigned long _size;
  void **_data;
  size_t _datasize;
};

typedef struct Vector* Vector;

Vector vector_create(size_t datasize) {
  Vector v = malloc(sizeof(struct Vector));
  v->_data = malloc(sizeof(void *) * VECTOR_INITIAL_CAPACITY);
  v->_capacity = VECTOR_INITIAL_CAPACITY;
  v->_size = 0;
  v->_datasize = datasize;

  return v;
}

void vector_destroy(Vector v) {
  free(v->_data);
  free(v);
}

void *vector_push(Vector v, void *value) {
  if (v->_size >= v->_capacity) {
    v->_capacity *= 2;
    v->_data = realloc(v->_data, v->_capacity * sizeof(void*));
  }

  v->_data[v->_size++] = value;
  return value;
};

unsigned long vector_size(Vector v) { return v->_size; }

unsigned long vector_capacity(Vector v) { return v->_capacity; }

void *vector_get(Vector v, unsigned long index) {
  if (index >= v->_size) {
    return NULL;
  }
  return v->_data[index];
}

void *vector_pop(Vector v) {
  if (v->_size <= 0) {
    v->_size = 0;
    return NULL;
  }

  void *value = v->_data[v->_size--];
  return value;
}

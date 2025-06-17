// Author: Daniil Shilo <tokiory>
// This file contains custom (and simple as fuck) implementation of hashmap
// based on FNV1A Hash function and linked lists Buckets in this implementation
// are hardcoded (255 buckets)
#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

#define FNV1A_32_OFFSET 0x811c9dc5u
#define FNV1A_32_PRIME 0x01000193u
#define HASHMAP_BUCKETS_AMOUNT 255

struct HashmapEntry {
  char *key;
  void *value;
  struct HashmapEntry *next;
};

struct Hashmap {
  struct HashmapEntry **_buckets;
};

Vector hashmap_entries(Hashmap h) {
  Vector entries = vector_create(sizeof(void*));
  for (unsigned i = 0; i < HASHMAP_BUCKETS_AMOUNT; i++) {
    HashmapEntry entry = h->_buckets[i];
    while (entry != NULL) {
      vector_push(entries, &(entry->value));
      entry = entry->next;
    }
  }
  return entries;
}

HashmapEntry _hashmap_entry_create(char *k, void *v) {
  HashmapEntry e = malloc(sizeof(struct HashmapEntry));
  e->key = k;
  e->value = v;
  e->next = NULL;
  return e;
}

void _hashmap_entry_destroy(HashmapEntry e) {
  free(e);
  e = NULL;
}

// FNV1A Hash function
// See: https://gist.github.com/ruby0x1/81308642d0325fd386237cfa3b44785c
unsigned int hashmap_hash(char *str) {
  const uint8_t *ptr = (const uint8_t *)str;
  unsigned int hash = FNV1A_32_OFFSET;
  while (*ptr) {
    hash ^= *ptr++;
    hash *= FNV1A_32_PRIME;
  }
  return hash;
}

unsigned int get_bucket_idx(char *key) {
  return hashmap_hash(key) % HASHMAP_BUCKETS_AMOUNT;
}

Hashmap hashmap_create() {
  Hashmap h = malloc(sizeof(struct Hashmap));
  h->_buckets = malloc(sizeof(HashmapEntry) * HASHMAP_BUCKETS_AMOUNT);

  for (unsigned i = 0; i < HASHMAP_BUCKETS_AMOUNT; i++) {
    h->_buckets[i] = NULL;
  }

  return h;
}

void hashmap_set(Hashmap h, char *key, void *value) {
  const unsigned bucket_idx = get_bucket_idx(key);
  HashmapEntry entry = h->_buckets[bucket_idx];

  if (entry == NULL) {
    h->_buckets[bucket_idx] = _hashmap_entry_create(key, value);
    return;
  }

  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      entry->value = value;
      return;
    }

    if (entry->next == NULL) {
      entry->next = _hashmap_entry_create(key, value);
      break;
    }
    
    entry = entry->next;
  }
}

void *hashmap_get(Hashmap h, char *key) {
  const unsigned bucket_idx = get_bucket_idx(key);
  HashmapEntry entry = h->_buckets[bucket_idx];

  for (HashmapEntry entry = h->_buckets[bucket_idx]; entry != NULL;
       entry = entry->next) {
    if (strcmp(entry->key, key) == 0) {
      return entry->value;
    }
  }

  return NULL;
}

void hashmap_del(Hashmap h, char *key) {
  const unsigned bucket_idx = get_bucket_idx(key);
  HashmapEntry entry = h->_buckets[bucket_idx];
  HashmapEntry previous_entry = NULL;

  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      if (previous_entry != NULL) {
        previous_entry->next = entry->next;
      } else {
        h->_buckets[bucket_idx] = entry->next;
      }
      _hashmap_entry_destroy(entry);
      return;
    }
    previous_entry = entry;
    entry = entry->next;
  }
}

void hashmap_destroy(Hashmap h) {
  for (int bucket_idx = 0; bucket_idx < HASHMAP_BUCKETS_AMOUNT; bucket_idx++) {
    for (HashmapEntry entry = h->_buckets[bucket_idx]; entry != NULL;) {
      HashmapEntry next_entry = entry->next;
      _hashmap_entry_destroy(entry);
      entry = next_entry;
    }
  }
}

typedef struct Hashmap *Hashmap;
typedef struct HashmapEntry *HashmapEntry;

void hashmap_set(Hashmap h, char *key, void *value);

void *hashmap_get(Hashmap h, char *key);

void hashmap_del(Hashmap h, char *key);

void hashmap_destroy(Hashmap h);

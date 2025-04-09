#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Tools.h"
#include "List.h"

typedef size_t (*HashFunction)(KeyType key);

typedef struct __HashTable {
    Node**       table;
    size_t       size;
    size_t       capacity;
    HashFunction hash_func;
} HashTable;

#endif // HASHTABLE_H
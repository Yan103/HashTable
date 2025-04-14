#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Tools.h"
#include "string.h"

#define TABLE_SIZE  100009 //* it is too big!      ????
#define LOAD_FACTOR 0.75

typedef const char* KeyType;
typedef size_t (*HashFunction)(KeyType key);

typedef struct __node {
    struct __node* next;
    struct __node* prev;
    KeyType        key;
    size_t         frequency;
} Node;

typedef struct __HashTable {
    Node**       table;
    size_t       size;
    size_t       capacity;
    HashFunction hash_func;
} HashTable;

Node* HashTableFind(Node* head, KeyType find_key);

ReturnCodes HashTableInsert(HashTable* ht, KeyType new_key);

ReturnCodes HashTableResize(HashTable* ht, size_t new_capacity);

HashTable* HashTableCtor(size_t table_size, HashFunction hash_func);

ReturnCodes HashTableDtor(HashTable* ht);

#endif // HASHTABLE_H
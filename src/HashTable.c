#include "HashTable.h"

Node* HashTableFind(Node* head, KeyType find_key) {
    while (head != NULL) {
        if (strcmp(head->key, find_key) == 0) return head;
        head = head->next;
    }

    return NULL;
}

ReturnCodes HashTableInsert(HashTable* ht, KeyType new_key) {
    assert(ht != NULL && "Null pointer was passed in HashTableInsert!\n");

    if ((double)ht->size / (double)ht->capacity >= LOAD_FACTOR) {
        fprintf(stdout, GREEN("RESIZE!\n"));
        HashTableResize(ht, ht->capacity * 2);
    }
    //if (HashTableFind(*head, new_key) == 1) return SUCCESS;

    //printf("aboba!\n");

    size_t hash     = ht->hash_func(new_key) % ht->capacity;
    Node*  existing = HashTableFind(ht->table[hash], new_key);

    if (existing != NULL) {
        existing->frequency++;
        return SUCCESS;
    }   

    char* key_copy = strdup(new_key); 
    if (key_copy == NULL) {
        return MEMORY_ERROR;
    }

    Node* new_node = (Node*) calloc(1, sizeof(Node));
    assert(new_node != NULL && "Memory error in HashTableInsert!\n");

    new_node->key       = key_copy;
    new_node->frequency = 1; 

    new_node->next = ht->table[hash];
    if (ht->table[hash] != NULL) {
        ht->table[hash]->prev = new_node;
    }
    ht->table[hash] = new_node;
    ht->size++;

    //printf("aboba!\n");

    return SUCCESS;
}

HashTable* HashTableCtor(size_t table_size, HashFunction hash_func) {
    assert(hash_func != NULL && "Null pointer was passed in HashTableCtor!\n");
    
    HashTable* ht = (HashTable*) calloc(1, sizeof(HashTable));
    if (ht == NULL) {
        fprintf(stderr, RED("Memory error in HashTableCtor!\n"));
        return NULL;
    }

    ht->table = (Node**) calloc(table_size, sizeof(Node*));
    if (ht->table == NULL) {
        fprintf(stderr, RED("Memory error in HashTableCtor!\n"));
        FREE(ht);
        return NULL;
    }

    ht->hash_func = hash_func;
    ht->size      = 0;
    ht->capacity  = table_size;
    
    return ht;
}

ReturnCodes HashTableDtor(HashTable* ht) {
    assert(ht != NULL && "Null pointer was passed in HashTableFree!\n");

    Node* curr = NULL, * tmp = NULL;
    for (size_t i = 0; i < ht->capacity; i++) {
        curr = ht->table[i];
        while (curr != NULL) {
            tmp = curr;
            curr = curr->next;
            free((void*)tmp->key);  
            FREE(tmp);
        }
        ht->table[i] = NULL;
    }

    FREE(ht->table);
    FREE(ht);

    return SUCCESS;
}

ReturnCodes HashTableResize(HashTable* ht, size_t new_capacity) {
    assert(ht != NULL && RED("Null pointer was passed in HashTableResize!\n"));

    Node** new_table = (Node**) calloc(new_capacity, sizeof(Node*));
    if (new_table == NULL) {
        fprintf(stderr, RED("Mmory error in HashTableResize!\n"));
        return MEMORY_ERROR;
    }

    Node** old_table    = ht->table;
    size_t old_capacity = ht->capacity;
    ht->size     = 0;
    ht->capacity = new_capacity;
    ht->table    = new_table;

    Node* curr = NULL, * next = NULL;
    size_t hash = 0;

    for (size_t i = 0; i < old_capacity; i++) {
        curr = old_table[i];
        while (curr != NULL) {
            next = curr->next;
            hash = ht->hash_func(curr->key) % ht->capacity;

            curr->next = new_table[hash];
            if (new_table[hash] != NULL) {
                new_table[hash]->prev = curr;
            }
            new_table[hash] = curr;
            ht->size++;

            curr = next;
        }
    }

    FREE(old_table);

    return SUCCESS;
}
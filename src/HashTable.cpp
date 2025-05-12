#include "HashTable.h"

const        size_t LEN_ALIGNMENT     = 16; 
static const size_t LENGTH_FIELD_SIZE = 2;

Node* HashTableFind(Node* head, KeyType* find_key) {
    while (head != NULL) {
        if (strcmp(head->key, find_key) == 0) return head;
        head = head->next;
    }
    return NULL;
}

int MyAsmStrCmp(KeyType* str1, KeyType* str2) {
    assert(str1 != NULL);
    assert(str2 != NULL);

    uint32_t len1 = *((uint32_t*)str1);
    uint32_t len2 = *((uint32_t*)str2);

    if (len1 != len2) return 1;

    const char* s1 = str1 + LENGTH_FIELD_SIZE;
    const char* s2 = str2 + LENGTH_FIELD_SIZE;

    size_t i = 0;
    for (; i + LEN_ALIGNMENT <= len1; i += LEN_ALIGNMENT) {
        __m128i xmm1 = _mm_loadu_si128((__m128i*)(s1 + i));
        __m128i xmm2 = _mm_loadu_si128((__m128i*)(s2 + i));
        __m128i cmp  = _mm_cmpeq_epi8(xmm1, xmm2);

        if (_mm_movemask_epi8(cmp) != 0xFFFF) return 1; 
    }

    //* remained
    for (; i < len1; ++i) {
        if (s1[i] != s2[i]) return 1;
    }

    return 0;
}

ReturnCodes HashTableInsert(HashTable* ht, KeyType* new_key) {
    assert(ht != NULL);

    if ((double)ht->size / (double)ht->capacity >= LOAD_FACTOR) {
        fprintf(stdout, GREEN("RESIZE!\n"));
        HashTableResize(ht, ht->capacity * 2);
    }

    size_t hash = ht->hash_func(new_key) & (ht->capacity - 1);
    Node* current = ht->table[hash];

    while (current != NULL) {
        if (MyAsmStrCmp(current->key, new_key) == 0) {
            current->frequency++;
            return SUCCESS;
        }
        current = current->next;
    }

    uint32_t len = *((uint32_t*)new_key);
    char* key_copy = (char*)malloc(LENGTH_FIELD_SIZE + len + 1);
    if (key_copy == NULL) return MEMORY_ERROR;
    
    memcpy(key_copy, new_key, LENGTH_FIELD_SIZE + len);
    key_copy[LENGTH_FIELD_SIZE + len] = '\0'; 

    Node* new_node = (Node*) aligned_alloc(LEN_ALIGNMENT, sizeof(Node)); 
    if (new_node == NULL) {
        FREE(key_copy);
        return MEMORY_ERROR;
    }
    memset(new_node, 0, sizeof(Node));

    new_node->key = key_copy;
    new_node->frequency = 1;
    new_node->next = ht->table[hash];
    new_node->prev = NULL;

    if (ht->table[hash] != NULL)
        ht->table[hash]->prev = new_node;

    ht->table[hash] = new_node;
    ht->size++;

    return SUCCESS;
}

HashTable* HashTableCtor(size_t table_size, HashFunction hash_func) {
    assert(hash_func != NULL);
    
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
    assert(ht != NULL);

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
    assert(ht != NULL);

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
            hash = ht->hash_func(curr->key) & (ht->capacity - 1);

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
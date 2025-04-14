#include "Tester.h"

ReturnCodes StartTestsForHashTable(HashTable* ht, const char* input, const char* output) {
    assert(ht != NULL && input != NULL && output != NULL && RED("Null pointer was passed in StartTestsForHashTable!\n"));

    FILE* tests = fopen(input, "r");
    if (tests == NULL) {
        fprintf(stderr, RED("Error with occured the file!\n"));
        return FILE_ERROR;
    }

    FILE* answer = fopen(output, "w");
    if (answer == NULL) {
        fprintf(stderr, RED("Error with occured the file!\n"));
        fclose(tests);
        return FILE_ERROR;
    }

    char* buffer = (char*) calloc(MAXLEN, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, RED("Memory error in ParseTextFromFile!\n"));
        fclose(tests);
        fclose(answer);
        return MEMORY_ERROR;
    }

    Node* find = NULL; 
    size_t hash = 0, found = 0;
    while (fscanf(tests, "%255s", buffer) == 1) {
        //printf("%s\n", buffer);
        hash = ht->hash_func(buffer) % ht->capacity;
        find = HashTableFind(ht->table[hash], buffer);
        if (find) found++;        
    }
    printf(GREEN("Found: %lu\n"), found);

    fclose(tests);
    fclose(answer);
    FREE(buffer);

    return SUCCESS;
}

ReturnCodes CalcCollisionsNumber(HashTable* ht, const char* output) {
    assert(ht != NULL && output != NULL && RED("Null pointer was passed in StartTestsForHashTable!\n"));

    FILE* answer = fopen(output, "w");
    if (answer == NULL) {
        fprintf(stderr, RED("Error with occured the file!\n"));
        return FILE_ERROR;
    } 

    size_t capacity = ht->capacity, collisions_per_hash = 0;
    int cnt = 0;
    for (size_t i = 0; i < capacity; i++) {
        collisions_per_hash = 0;
        if (ht->table[i]) {
            cnt++;
            Node* curr = ht->table[i];
            while (curr != NULL) {
                collisions_per_hash += curr->frequency;
                curr = curr->next;
            }
        }
        fprintf(answer, "%lu %d\n", i, collisions_per_hash);
    }
    printf(RED("%d\n"), cnt);


    fclose(answer);

    return SUCCESS;
}

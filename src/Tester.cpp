#include "Tester.h"
#include "time.h"

static const size_t MAXLEN            = 256;
static const size_t LENGTH_FIELD_SIZE = 4;

ReturnCodes StartTestsForHashTable(HashTable* ht, const char* input, const char* output) {
    assert(ht     != NULL);
    assert(input  != NULL);
    assert(output != NULL);

    FILE* tests = fopen(input, "r");
    if (tests == NULL) {
        fprintf(stderr, RED("Error opening input file!\n"));
        return FILE_ERROR;
    }

    FILE* answer = fopen(output, "w");
    if (answer == NULL) {
        fprintf(stderr, RED("Error opening output file!\n"));
        fclose(tests);
        return FILE_ERROR;
    }

    char* buffer = (char*)calloc(LENGTH_FIELD_SIZE + MAXLEN + 1, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, RED("Memory error!\n"));
        fclose(tests);
        fclose(answer);
        return MEMORY_ERROR;
    }

    size_t total_time = 0;
    size_t operations = 0;
    size_t found = 0;
    char* str_ptr = buffer + LENGTH_FIELD_SIZE;

    while (fscanf(tests, "%255s", str_ptr) == 1) {
        char* end = str_ptr;
        while (*end) ++end;
        uint32_t len = (uint32_t)(end - str_ptr);
        *((uint32_t*)buffer) = len;

        size_t start   = __rdtsc();
        size_t hash    = ht->hash_func(buffer) & (ht->capacity - 1);
        Node* find     = HashTableFind(ht->table[hash], buffer);
        size_t op_time = __rdtsc() - start;
        
        if (find) {
            found++;
        }
        
        total_time += op_time;
        operations++;
    }

    printf(GREEN("Total searches: %lu\n"), operations);
    printf(GREEN("Total time: %lu tacts\n"), total_time);
    printf(GREEN("Average time per search: %.2f tacts\n"), (double)total_time / operations);

    FREE(buffer);
    fclose(tests);
    fclose(answer);

    return SUCCESS;
}


ReturnCodes CalcCollisionsNumber(HashTable* ht, const char* output) {
    assert(ht     != NULL);
    assert(output != NULL);

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
        fprintf(answer, "%lu %lu\n", i, collisions_per_hash);
    }
    printf(RED("%d\n"), cnt);

    fclose(answer);

    return SUCCESS;
}

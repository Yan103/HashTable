#include "TextParser.h"

static const size_t MAXLEN = 256;
static const size_t LENGTH_FIELD_SIZE = 4;

ReturnCodes ParseTextFromFile(const char* filename, HashTable* ht) {
    assert(filename != NULL);
    assert(ht       != NULL);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, RED("Error with open the file {}!\n"));
        return FILE_ERROR;
    }

    char* buffer = (char*) calloc(MAXLEN + LENGTH_FIELD_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, RED("Memory error in ParseTextFromFile!\n"));
        fclose(file);
        return MEMORY_ERROR;
    }

    int cnt = 0;
    while (fscanf(file, "%255s", buffer + LENGTH_FIELD_SIZE) == 1) {
        cnt++;
        size_t len = strlen(buffer + LENGTH_FIELD_SIZE);
        
        *((uint32_t*)buffer) = (uint32_t)len;
        
        HashTableInsert(ht, buffer);
    }
    printf(GREEN("%d\n"), cnt);

    FREE(buffer);
    fclose(file);

    return SUCCESS;
}

#include "TextParser.h"

static const size_t MAXLEN = 256;

ReturnCodes ParseTextFromFile(const char* filename, HashTable* ht) {
    assert(filename != NULL && ht != NULL && RED("Null pointer was passed!\n"));

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, RED("Error with open the file {}!\n"));
        return FILE_ERROR;
    }

    char* buffer = (char*) calloc(MAXLEN, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, RED("Memory error in ParseTextFromFile!\n"));
        fclose(file);
        return MEMORY_ERROR;
    }

    int cnt = 0;
    while (fscanf(file, "%255s", buffer) == 1) {
        //printf("%s\n", buffer);
        cnt++;
        HashTableInsert(ht, buffer);
    }
    printf(GREEN("%d\n"), cnt);

    FREE(buffer);
    fclose(file);

    return SUCCESS;
}

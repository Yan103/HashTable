#include "TextParser.h"

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
        return FILE_ERROR;
    }

    //long long cnt = 0;
    while (fscanf(file, "%255s", buffer) == 1) {
        //printf("%s\n", buffer);
        //cnt++;
        HashTableInsert(ht, buffer);
    }
    //printf(GREEN("%lld\n"), cnt);

    FREE(buffer);
    fclose(file);

    return SUCCESS;
}

#include "Tools.h"
#include "HashFucntions.h"
#include "TextParser.h"

int main() {

    HashTable* ht = HashTableCtor(TABLE_SIZE, GetHashWordLength);
    if (ht == NULL) {
        fprintf(stderr, RED("Error in HashTableCtor!\n"));
        return MEMORY_ERROR;
    }

    printf("%lu\n", ht->size);
    ParseTextFromFile("LOR.txt", ht);
    printf("%lu\n", ht->size);

    const char* s = "Lord";
    size_t hash = ht->hash_func(s) % ht->size;

    printf("%s\n", ht->table[hash]->key);
    //printf("Searching for '%s'...\n", s);
    //Node* find = HashTableFind(ht->table[hash], s);
    //if (find) {
    //    printf(GREEN("Found: %s\n"), find->key);
    //} else {
    //    printf(RED("Not found!\n"));
    //}

    HashTableDtor(ht);

    return SUCCESS;   
}
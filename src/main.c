#include "Tools.h"
#include "HashFucntions.h"
#include "TextParser.h"

int main() {

    HashTable* ht = HashTableCtor(TABLE_SIZE, GetHashCRC32);
    if (ht == NULL) {
        fprintf(stderr, RED("Error in HashTableCtor!\n"));
        return MEMORY_ERROR;
    }

    ParseTextFromFile("LOR_converted.txt", ht);
    printf("%lu\n", ht->size);
    printf(GREEN("Parse stage end!\n"));

    const char* s = "Lord";
    size_t hash = ht->hash_func(s) % ht->capacity;

    printf("Searching for '%s'...\n", s);
    Node* find = HashTableFind(ht->table[hash], s);
    if (find) {
        printf(GREEN("Found: %s\n"), find->key);
    } else {
        printf(RED("Not found!\n"));
    }

    HashTableDtor(ht);

    return SUCCESS;   
}
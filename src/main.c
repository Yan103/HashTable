#include "Tools.h"
#include "HashFucntions.h"
#include "TextParser.h"
#include "Tester.h"

int main() {
    HashTable* ht = HashTableCtor(TABLE_SIZE, GetHashCRC32);
    if (ht == NULL) {
        fprintf(stderr, RED("Error in HashTableCtor!\n"));
        return MEMORY_ERROR;
    }

    ParseTextFromFile("LOR_converted.txt", ht);
    printf(GREEN("Parse stage end! Size: %lu\n"), ht->size);
    
    //StartTestsForHashTable(ht, "mixed_test.txt", "test_results.txt");
    CalcCollisionsNumber(ht, "collisions.txt");

    HashTableDtor(ht);

    return SUCCESS;   
}
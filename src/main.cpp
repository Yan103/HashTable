#include "Tools.h"
#include "HashFucntions.h"
#include "TextParser.h"
#include "Tester.h"

//* valgrind --tool=callgrind ./build/hashtable 
//* kcachegrind callgrind.out

//* translate ast in asm
//* think about steck calculate

static const char* LORD_OF_RINGS_TEXT = "LOR_converted.txt";
static const char* SHUFFLE_TEST       = "mixed_test.txt";
static const char* RESULTS_FILE       = "test_results.txt";

int main() {
    HashTable* ht = HashTableCtor(TABLE_SIZE, GetHashCRC32Default);
    if (ht == NULL) {
        fprintf(stderr, RED("Error in HashTableCtor!\n"));
        return MEMORY_ERROR;
    }

    ParseTextFromFile(LORD_OF_RINGS_TEXT, ht);
    printf(GREEN("Parse stage end! Size: %lu\n"), ht->size);
    
    StartTestsForHashTable(ht, SHUFFLE_TEST, RESULTS_FILE);

    HashTableDtor(ht);

    return SUCCESS;   
}
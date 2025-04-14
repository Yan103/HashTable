#ifndef TESTER_H
#define TESTER_H

#include "Tools.h"
#include "HashTable.h"

#define MAXLEN 256

ReturnCodes StartTestsForHashTable(HashTable* ht, const char* input, const char* output);

ReturnCodes CalcCollisionsNumber(HashTable* ht, const char* output);

#endif // TESTER_H
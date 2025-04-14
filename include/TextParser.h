#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include "Tools.h"
#include "HashTable.h"
#include "HashFucntions.h"

#define MAXLEN 256

ReturnCodes ParseTextFromFile(const char* filename, HashTable* ht);

#endif // TEXTPARSER_H
#include "HashFucntions.h"

size_t GetHashWordLength(KeyType* key) {
    assert(key != NULL);

    return strlen((const char*)key);
}

size_t GetHashASCIISum(KeyType* key) {
    assert(key != NULL);

    size_t len = strlen(key);
    size_t sum = 0;

    for (size_t i = 0; i < len; i++) {
        sum += (size_t)key[i];
    }

    return sum;
}

size_t GetHashASCIIAverage(KeyType* key) {
    assert(key != NULL);

    size_t len = strlen(key);
    size_t sum = 0;

    for (size_t i = 0; i < len; i++) {
        sum += (size_t)key[i];
    }

    return sum / len;
}

size_t GetHashPolynomial(KeyType* key) {
    assert(key != NULL);

    size_t hash = 0;

    for (; *key; ++key) {
        hash = hash * 31 + (unsigned char)*key;
    }
    return hash;
}

size_t GetHashDJB2(KeyType* key) {
    assert(key != NULL);

    size_t hash = 1379; //* my default parameter
    int       c = 0;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + (size_t)c; 
    }

    return hash;
}

size_t GetHashCRC32Default(KeyType* key) {
    assert(key != NULL);

    size_t size = strlen(key);
    size_t crc  = 0xffffffff;

	while (size-- != 0) {
        crc = (crc << 8) ^ crc32_table[((crc >> 24) ^ (size_t)*key) & 255];
        key++;
    }

    return crc;
}


size_t GetHashCRC32Optimize(KeyType* key) {
    assert(key != NULL);

    size_t size = strlen(key);
    size_t crc  = 0xffffffff;
    
    for (size_t i = 0; i < size; i++) {
        asm volatile (
            "crc32b %1, %0"
            : "+r"(crc)
            : "rm"(*key)
        );
        key++;
    }

    return crc;
}

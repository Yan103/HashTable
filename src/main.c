#include "Tools.h"
#include "HashFucntions.h"

int main() {
    KeyType key = "Test my hash fucntions";

    printf("Len hash:        %lu\n", GetHashWordLength(key));
    printf("Sum ASCII:       %lu\n", GetHashASCIISum(key));
    printf("Average ASCII:   %lu\n", GetHashASCIIAverage(key));
    printf("Polynomial hash: %lu\n", GetHashPolinomial(key));
    printf("DJB2  hash:      %lu\n", GetHashDJB2(key));
    printf("CRC32 hash:      %lu\n", GetHashCRC32(key));

    return 0;   
}
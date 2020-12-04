/* Day 4, part 1 = 210 */

#include <stdio.h>
#include <string.h>

int allThere(int keyValuePairsCount, char keyValuePairs[][20]) {
    char *requiredKeys[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
    int requiredKeyCount = sizeof(requiredKeys) / sizeof(*requiredKeys);
    char keyValueSeparator[] = ":";
    char *key;
    char allKeys[32] = "";

    for (int i = 0; i < keyValuePairsCount; i++) {
        if ((key = strtok(keyValuePairs[i], keyValueSeparator))) {
            strcpy(allKeys + strlen(allKeys), key);
        }
    }

    int allThere = 1;

    for (int i = 0; allThere && i < requiredKeyCount; i++) {
        if (!strstr(allKeys, requiredKeys[i])) {
            allThere = 0;
        }
    }

    return allThere;
}

int main() {
    FILE *batchesFile = fopen("batches.txt", "r");

    if (batchesFile) {
        char dataLine[100];
        char dataLineLength;
        char keyValuePairs[10][20];
        int keyValuePairsCount = 0;
        int validCount = 0;

        while (fgets(dataLine, sizeof(dataLine), batchesFile)) {
            dataLineLength = strlen(dataLine);

            if (dataLine[dataLineLength - 1] == '\n') {
                dataLine[dataLineLength - 1] = 0;
                --dataLineLength;
            }

            if (dataLineLength == 0) {
                if (allThere(keyValuePairsCount, keyValuePairs)) {
                    ++validCount;
                }

                keyValuePairsCount = 0;
            } else {
                char keyValuePairSeparator[] = " ";
                char *keyValuePtr = strtok(dataLine, keyValuePairSeparator);

                while (keyValuePtr) {
                    strcpy(keyValuePairs[keyValuePairsCount++], keyValuePtr);

                    keyValuePtr = strtok(NULL, keyValuePairSeparator);                
                }
            }
        }

        fclose(batchesFile);

        if (keyValuePairsCount > 0) {
            if (allThere(keyValuePairsCount, keyValuePairs)) {
                ++validCount;
            }
        }

        printf("%d", validCount);
    }

    return 0;
}
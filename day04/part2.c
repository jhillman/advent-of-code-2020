/* Day 4, part 2 = 131 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct YearRange {
    int min;
    int max;
};

int yearValid(char *yearString, struct YearRange yearRange) {
    if (strlen(yearString) != 4) {
        return 0;
    }

    int year;

    if (sscanf(yearString, "%d", &year) != 1) {
        return 0;
    }

    return year >= yearRange.min && year <= yearRange.max;
}

int heightValid(char *height) {
    int value;

    if (strstr(height, "cm") && sscanf(height, "%dcm", &value) == 1) {
        return value >= 150 && value <= 193;
    } else if (strstr(height, "in") && sscanf(height, "%din", &value) == 1) {
        return value >= 59 && value <= 76;
    }

    return 0;
}

int hairColorValid(char *hairColor) {
    if (strlen(hairColor) != 7 || *hairColor != '#') {
        return 0;
    }

    char characters[7];
    char character;

    if (sscanf(hairColor + 1, "%s", characters) != 1) {
        return 0;
    }

    int valid = 1;

    for (int i = 0; valid && i < 6; i++) {
        character = characters[i];

        valid = (character >= '0' && character <= '9') || (character >= 'a' && character <= 'f');
    }

    return 1;
}

int eyeColorValid(char *eyeColor) {
    if (strlen(eyeColor) != 3) {
        return 0;
    }

    char *colors[] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
    int colorCount = sizeof(colors) / sizeof(*colors);
    int valid = 0;

    for (int i = 0; !valid && i < colorCount; i++) {
        if (strcmp(eyeColor, colors[i]) == 0) {
            valid = 1;
        }
    }

    return valid;
}

int passportIdValid(char *passportIdString) {
    if (strlen(passportIdString) != 9) {
        return 0;
    }

    int passportId;

    if (sscanf(passportIdString, "%9d", &passportId) == 1) {
        return 1;
    }

    return 0;
}

int allThereAndValid(int keyValuePairsCount, char keyValuePairs[][20]) {
    struct YearRange birthYearRange = { 1920, 2002 };
    struct YearRange issueYearRange = { 2010, 2020 };
    struct YearRange expirationYearRange = { 2020, 2030 };

    char *requiredKeys[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
    int requiredKeyCount = sizeof(requiredKeys) / sizeof(*requiredKeys);
    char keyValueSeparator[] = ":";
    char *key;
    char *value;
    int valid = 1;
    char allKeys[32] = "";

    for (int i = 0; valid && i < keyValuePairsCount; i++) {
        if ((key = strtok(keyValuePairs[i], keyValueSeparator))) {
            strcpy(allKeys + strlen(allKeys), key);

            value = strtok(NULL, keyValueSeparator);

            if (strcmp(key, "byr") == 0) {
                valid = yearValid(value, birthYearRange);
            } else if (strcmp(key, "iyr") == 0) {
                valid = yearValid(value, issueYearRange);
            } else if (strcmp(key, "eyr") == 0) {
                valid = yearValid(value, expirationYearRange);
            } else if (strcmp(key, "hgt") == 0) {
                valid = heightValid(value);
            } else if (strcmp(key, "hcl") == 0) {
                valid = hairColorValid(value);
            } else if (strcmp(key, "ecl") == 0) {
                valid = eyeColorValid(value);
            } else if (strcmp(key, "pid") == 0) {
                valid = passportIdValid(value);
            }
        }
    }

    for (int i = 0; valid && i < requiredKeyCount; i++) {
        if (!strstr(allKeys, requiredKeys[i])) {
            valid = 0;
        }
    }

    return valid;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char dataLine[100];
        char dataLineLength;
        char keyValuePairs[10][20];
        int keyValuePairsCount = 0;
        int validCount = 0;

        while (fgets(dataLine, sizeof(dataLine), inputFile)) {
            dataLineLength = strlen(dataLine);

            if (dataLine[dataLineLength - 1] == '\n') {
                dataLine[dataLineLength - 1] = 0;
                --dataLineLength;
            }

            if (dataLineLength == 0) {
                if (allThereAndValid(keyValuePairsCount, keyValuePairs)) {
                    ++validCount;
                }

                keyValuePairsCount = 0;
            } else {
                char keyValuePairSeparator[] = " ";
                char *keyValuePtr = strtok(dataLine, keyValuePairSeparator);

                while (keyValuePtr) {
                    if (!strstr(keyValuePtr, "cid")) {
                        strcpy(keyValuePairs[keyValuePairsCount++], keyValuePtr);
                    }

                    keyValuePtr = strtok(NULL, keyValuePairSeparator);                
                }
            }
        }

        fclose(inputFile);

        if (keyValuePairsCount > 0) {
            if (allThereAndValid(keyValuePairsCount, keyValuePairs)) {
                ++validCount;
            }
        }

        printf("%d", validCount);
    }

    return 0;
}
/* Day 2, part 1 = 655 */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char passwordData[50];
        int rangeStart;
        int rangeEnd;
        char character;
        char password[20];
        int passwordLength;
        int characterCount;
        int validCount = 0;

        while (fgets(passwordData, sizeof(passwordData), inputFile)) {
            sscanf(passwordData, "%d-%d %c: %s", &rangeStart, &rangeEnd, &character, password);

            passwordLength = strlen(password);
            characterCount = 0;

            for (int i = 0; i < passwordLength; i++) {
                if (*(password + i) == character) {
                    ++characterCount;
                }
            }

            if (characterCount >= rangeStart && characterCount <= rangeEnd) {
                ++validCount;
            }
        }

        fclose(inputFile);

        printf("%d", validCount);
    }

    return 0;
}
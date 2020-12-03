/* Day 2, part 1 = 655 */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *passwordsFile = fopen("passwords.txt", "r");
    char passwordData[50];
    int rangeStart;
    int rangeEnd;
    char character;
    char password[20];
    int passwordLength;
    int characterCount;
    int i;
    int validCount = 0;

    if (passwordsFile) {
        while (fgets(passwordData, 50, passwordsFile)) {
            sscanf(passwordData, "%d-%d %c: %s", &rangeStart, &rangeEnd, &character, password);

            passwordLength = strlen(password);
            characterCount = 0;

            for (i = 0; i < passwordLength; i++) {
                if (*(password + i) == character) {
                    ++characterCount;
                }
            }

            if (characterCount >= rangeStart && characterCount <= rangeEnd) {
                ++validCount;
            }
        }

        fclose(passwordsFile);

        printf("%d", validCount);
    }

    return 0;
}
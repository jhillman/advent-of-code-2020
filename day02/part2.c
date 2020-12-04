/* Day 2, part 2 = 673 */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *passwordsFile = fopen("passwords.txt", "r");

    if (passwordsFile) {
        char passwordData[50];
        int positionOne;
        int positionTwo;
        char character;
        char password[20];
        char characterOne;
        char characterTwo;
        int validCount = 0;

        while (fgets(passwordData, sizeof(passwordData), passwordsFile)) {
            sscanf(passwordData, "%d-%d %c: %s", &positionOne, &positionTwo, &character, password);

            characterOne = password[positionOne - 1];
            characterTwo = password[positionTwo - 1];

            if (characterOne == character && characterTwo != character) {
                ++validCount;
            } else if (characterTwo == character && characterOne != character) {
                ++validCount;
            }
        }

        fclose(passwordsFile);

        printf("%d", validCount);
    }

    return 0;
}
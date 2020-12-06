/* Day 6, part 1 = 6249 */

#include <stdio.h>
#include <string.h>

void resetCharacterCounts(int characterCounts[]) {
    for (int i = 0; i < 26; i++) {
        characterCounts[i] = 0;
    }
}

int answerCount(int characterCounts[]) {
    int count = 0;

    for (int i = 0; i < 26; i++) {
        count += characterCounts[i];
    }

    return count;
}

int main() {
    FILE *groupsFile = fopen("groups.txt", "r");

    if (groupsFile) {
        char answersLine[50];
        char answersLineLength;
        int characterCounts[26];
        int sum = 0;

        resetCharacterCounts(characterCounts);

        while (fgets(answersLine, sizeof(answersLine), groupsFile)) {
            answersLineLength = strlen(answersLine);

            if (answersLine[answersLineLength - 1] == '\n') {
                answersLine[answersLineLength - 1] = 0;
                --answersLineLength;
            }

            if (answersLineLength == 0) {
                sum += answerCount(characterCounts);

                resetCharacterCounts(characterCounts);
            } else {
                for (int i = 0; i < answersLineLength; i++) {
                    characterCounts[answersLine[i] - 'a'] = 1;
                }
            }
        }

        fclose(groupsFile);

        sum += answerCount(characterCounts);

        printf("%d", sum);
    }

    return 0;
}
/* Day 6, part 2 = 3103 */

#include <stdio.h>
#include <string.h>

void resetCharacterCounts(int characterCounts[]) {
    for (int i = 0; i < 26; i++) {
        characterCounts[i] = 0;
    }
}

int answerCount(int characterCounts[], int groupSize) {
    int count = 0;

    for (int i = 0; i < 26; i++) {
        if (characterCounts[i] == groupSize) {
            count += 1;
        }
    }

    return count;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char answersLine[50];
        char answersLineLength;
        int characterCounts[26];
        int groupSize = 0;
        int sum = 0;

        resetCharacterCounts(characterCounts);

        while (fgets(answersLine, sizeof(answersLine), inputFile)) {
            answersLineLength = strlen(answersLine);

            if (answersLine[answersLineLength - 1] == '\n') {
                answersLine[answersLineLength - 1] = 0;
                --answersLineLength;
            }

            if (answersLineLength == 0) {
                sum += answerCount(characterCounts, groupSize);

                resetCharacterCounts(characterCounts);

                groupSize = 0;
            } else {
                for (int i = 0; i < answersLineLength; i++) {
                    ++characterCounts[answersLine[i] - 'a'];
                }

                ++groupSize;
            }
        }

        fclose(inputFile);

        sum += answerCount(characterCounts, groupSize);

        printf("%d", sum);
    }

    return 0;
}
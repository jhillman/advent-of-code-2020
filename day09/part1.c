/* Day 9, part 1 = 375054920 */

#include <stdio.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int numberCount = 0;
        char ch;

        while (!feof(inputFile)) {
            ch = fgetc(inputFile);

            if (ch == '\n') {
                ++numberCount;
            }
        }

        if (ch != '\n' && numberCount > 0) {
            ++numberCount;
        }

        fseek(inputFile, 0, SEEK_SET);

        long numbers[numberCount];
        int numberIndex = 0;
        long number;

        while (numberIndex < numberCount) {
            fscanf(inputFile, "%ld", &number);

            numbers[numberIndex++] = number;
        }

        fclose(inputFile);

        int preambleLength = 25;
        int invalidNumber = 0;

        for (int i = preambleLength; !invalidNumber && i < numberCount; i++) {
            int number = numbers[i];
            int numberFound = 0;

            for (int j = i - preambleLength; !numberFound && j < i; j++) {
                int addend1 = numbers[j];

                for (int k = j + 1; !numberFound && k < i; k++) {
                    int addend2 = numbers[k];

                    if (addend1 + addend2 == number) {
                        numberFound = 1;
                    }
                }
            }

            if (!numberFound) {
                invalidNumber = number;
            }
        }

       printf("%d", invalidNumber);
    }

    return 0;
}

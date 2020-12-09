/* Day 9, part 2 = 54142584 */

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

        long invalidNumber = 375054920;
        long weakness = 0;

        for (int i = 0; !weakness && i < numberCount; i++) {
            long sum = numbers[i];
            long largest = numbers[i];
            long smallest = numbers[i];

            for (int j = i + 1; !weakness && sum < invalidNumber && j < numberCount; j++) {
                sum += numbers[j];

                if (numbers[j] > largest) {
                    largest = numbers[j];
                } else if (numbers[j] < smallest) {
                    smallest = numbers[j];
                }

                if (sum == invalidNumber) {
                    weakness = largest + smallest;
                }
            }
        }

       printf("%ld", weakness);
    }

    return 0;
}

/* Day 1, part 2 = 49214880 */

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

int main() {
    FILE *numbersFile = fopen("numbers.txt", "r");
    int numberCount = 200;
    int targetSum = 2020;
    int i;
    int j;
    int k;
    int numbers[numberCount];
    int number;
    int addend1;
    int addend2;
    int addend3;
    int found = 0;

    if (numbersFile) {
        for (i = 0; i < numberCount; i++) {
            fscanf(numbersFile, "%d", &number);
            numbers[i] = number;
        }

        fclose(numbersFile);

        qsort(numbers, numberCount, sizeof(int), compare);

        for (i = 0; !found && i < numberCount; i++) {
            addend1 = numbers[i];

            for (j = numberCount - 1; !found && j > i; j--) {
                addend2 = numbers[j];

                for (k = numberCount - 1; !found && k > j; k--) {
                    addend3 = numbers[k];

                    if (addend1 + addend2 + addend3 == targetSum) {
                        found = 1;
                    }
                }
            }
        }

        printf("%d", addend1 * addend2 * addend3);
    }

    return 0;
}
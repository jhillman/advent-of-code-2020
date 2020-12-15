#include <stdio.h>
#include <stdlib.h>

int playGame(int turnCount) {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int position = 0;
        int number;
        char ch;
        int *positions = (int *) calloc(turnCount, sizeof(int));
        int *ages = (int *) calloc(turnCount, sizeof(int));

        while (fscanf(inputFile, "%d%c", &number, &ch) >= 1) {
            positions[number] = position + 1;

            ++position;
        }

        fclose(inputFile);

        while (position < turnCount) {
            if (ages[number] > 0) {
                number = ages[number];
            } else {
                number = 0;
            }

            if (positions[number] > 0) {
                ages[number] = position - (positions[number] - 1);
            }

            positions[number] = position + 1;

            ++position;
        }

        free(positions);
        free(ages);

        return number;
    }

    return 0;
}

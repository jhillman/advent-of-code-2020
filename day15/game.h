#include <stdio.h>
#include <stdlib.h>

int playGame(int turnCount) {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int position = 0;
        int number;
        char ch;
        int *positions = (int *) calloc(turnCount, sizeof(int));

        while (fscanf(inputFile, "%d%c", &number, &ch) >= 1) {
            positions[number] = position + 1;

            ++position;
        }

        fclose(inputFile);

        int firstTime = 1;
        int age;

        while (position < turnCount) {
            if (firstTime) {
                positions[number] = position;

                number = 0;
            } else {
                age = position - positions[number];
                positions[number] = position;

                number = age;
            }

            firstTime = positions[number] == 0;

            ++position;
        }

        free(positions);

        return number;
    }

    return 0;
}

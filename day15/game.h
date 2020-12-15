#include <stdio.h>
#include <stdlib.h>

struct NumberStats {
    int position;
    int age;
};

int playGame(int turnCount) {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int position = 0;
        int number;
        char ch;
        struct NumberStats *stats = (struct NumberStats *) calloc(turnCount, sizeof(struct NumberStats));

        while (fscanf(inputFile, "%d%c", &number, &ch) >= 1) {
            stats[number].position = position + 1;

            ++position;
        }

        fclose(inputFile);

        while (position < turnCount) {
            if (stats[number].age > 0) {
                number = stats[number].age;
            } else {
                number = 0;
            }

            if (stats[number].position > 0) {
                stats[number].age = position - (stats[number].position - 1);
            }

            stats[number].position = position + 1;

            ++position;
        }

        free(stats);

        return number;
    }

    return 0;
}

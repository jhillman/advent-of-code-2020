/* Day 3, part 1 = 216 */

#include <stdio.h>
#include <string.h>

#define RIGHT 3
#define DOWN 1

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char mapLine[40];
        char mapLineLength;
        int downPosition = 0;
        int rightPosition = 0;
        int treeCount = 0;

        while (fgets(mapLine, sizeof(mapLine), inputFile)) {
            mapLineLength = strlen(mapLine);

            if (mapLine[mapLineLength - 1] == '\n') {
                --mapLineLength;
            }

            if (rightPosition == 0 && downPosition == 0 && *mapLine == '#') {
                ++treeCount;
            }

            if (downPosition == DOWN) {
                rightPosition += RIGHT;

                if (mapLine[rightPosition % mapLineLength] == '#') {
                   ++treeCount;
                }

                downPosition = 0;
            }

            ++downPosition;
        }

        fclose(inputFile);

        printf("%d", treeCount);
    }

    return 0;
}
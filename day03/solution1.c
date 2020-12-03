/* Day 3, part 1 = 216 */

#include <stdio.h>
#include <string.h>

#define RIGHT 3
#define DOWN 1

int main() {
    FILE *mapFile = fopen("map.txt", "r");
    char mapLine[40];
    char mapLineLength;
    int downPosition = 0;
    int rightPosition = 0;
    int treeCount = 0;

    if (mapFile) {
        while (fgets(mapLine, sizeof(mapLine), mapFile)) {
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

        fclose(mapFile);

        printf("%d", treeCount);
    }

    return 0;
}
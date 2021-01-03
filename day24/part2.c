/* Day 24, part 2 = ? */

#include <stdio.h>
#include "tiles.h"

int main() {
    struct Tile *current = getTiles();

    if (current) {
        struct Tile *copy;

        for (int i = 0; i < 10; i++) {
            expandTiles(current);

            freeTile(copy);
            copy = copyTiles(current);

            current = updateTiles(current, copy);

            printf("Day %d: %d\n\n", i + 1, countAllBlackTiles(current));
        }

        freeTile(current);
        freeTile(copy);
    }

    return 0;
}

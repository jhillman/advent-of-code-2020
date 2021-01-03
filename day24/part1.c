/* Day 24, part 1 = 254 */

#include <stdio.h>
#include "tiles.h"

int main() {
    struct Tile *center = getTiles();

    if (center) {
        printf("%d", countAllBlackTiles(center));

        freeTile(center);
    }

    return 0;
}

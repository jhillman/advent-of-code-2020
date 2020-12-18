/* Day 17, part 2 = 960 */

#include <stdio.h>
#include "space.h"

int main() {
    struct Space *space = readSpace(1);

    if (space) {
        for (int i = 0; i < 6; i++) {
            space = cycleSpace(space);
        }

        int activeCount = activeCubeCount(space);

        freeSpace(space);

        printf("%d", activeCount);
    }

    return 0;
}

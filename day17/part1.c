/* Day 17, part 1 = 286 */

#include <stdio.h>
#include "space.h"

int main() {
    struct Space *space = readSpace(0);

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

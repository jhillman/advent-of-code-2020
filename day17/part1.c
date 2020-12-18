/* Day 17, part 1 = 286 */

#include <stdio.h>
#include "pocket.h"

int main() {
    struct PocketDimension *pocketDimension = readPocketDimension(false);

    if (pocketDimension) {
        for (int i = 0; i < 6; i++) {
            pocketDimension = cyclePocketDimension(pocketDimension);
        }

        int activeCount = activeCubeCount(pocketDimension);

        freePocketDimension(pocketDimension);

        printf("%d", activeCount);
    }

    return 0;
}

/* Day 19, part 1 = 187 */

#include <stdio.h>
#include "match.h"

int main() {
    struct RulesData *data = readRulesData();

    if (data) {
        int validCount = validInputCount(data);

        freeRulesData(data);

        printf("%d", validCount);
    }

    return 0;
}

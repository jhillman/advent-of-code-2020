/* Day 23, part 1 = 27956483 */

#include <stdio.h>
#include "cups.h"

int main() {
    struct CupData *data = readCupData();

    if (data) {
        struct Cup *cup = data->first;

        for (int i = 0; i < 100; i++) {
            cup = move(cup, data->cupLookup, data->cupCount);
        }

        cup = data->cupLookup[1]->next;

        do {
            printf("%d", cup->label);
            cup = cup->next;
        } while (cup->label != 1);

        freeCupData(data);
    }

    return 0;
}

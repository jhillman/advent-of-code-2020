/* Day 16, part 1 = 27898 */

#include <stdio.h>
#include "tickets.h"

int main() {
    struct TicketData *data = getTicketData();

    if (data) {
        int invalidSum = 0;

        for (int i = 0; i < data->nearbyCount; i++) {
            for (int j = 0; j < data->valueCount; j++) {
                if (!data->nearby[i].values[j].valid) {
                    invalidSum += data->nearby[i].values[j].value;
                }
            }
        }

        freeTicketData(data);

        printf("%d", invalidSum);
    }

    return 0;
}

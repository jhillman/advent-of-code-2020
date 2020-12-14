/* Day 13, part 1 = 156 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int timestamp;

        fscanf(inputFile, "%d", &timestamp);

        char busSchedule[200];
        int minWaitTime = -1;

        if (fscanf(inputFile, "%s", busSchedule)) {
            char *busId = strtok(busSchedule, ",");

            while (busId) {
                if (*busId != 'x') {
                    int busDeparture = atoi(busId);

                    int busTime = busDeparture;

                    while (busTime < timestamp) {
                        busTime += busDeparture;
                    }

                    int waitTime = busDeparture * (busTime - timestamp);

                    if (minWaitTime == -1 || waitTime < minWaitTime) {
                        minWaitTime = waitTime;
                    }
                }

                busId = strtok(NULL, ",");
            }
        }

        fclose(inputFile);

        printf("%d", minWaitTime);
    }

    return 0;
}

/* Day 13, part 2 = 404517869995362 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long modularMultiplicativeInverse(long long number, long long modulus) {
    long long target = number % modulus;

    for (long long x = 1; x < modulus; x++) {
        if ((target * x) % modulus == 1) {
            return x;
        }
    }

    return 1;
}

long long chineseRemainder(int *modulii, int *residues, int count) {
    long long sum = 0;
    long long product = 1;

    for (int i = 0; i < count; i++) {
        product *= modulii[i];
    }

    for (int i = 0; i < count; i++) {
        long long p = product / modulii[i];

        sum += residues[i] * modularMultiplicativeInverse(p, modulii[i]) * p;
    }

    return sum % product;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        int timestamp;
        fscanf(inputFile, "%d", &timestamp);

        long busScheduleLocation = ftell(inputFile);
        char busSchedule[200];
        int busCount = 0;

        if (fscanf(inputFile, "%s", busSchedule)) {
            char *busId = strtok(busSchedule, ",");

            while (busId) {
                if (*busId != 'x') {
                    ++busCount;
                }

                busId = strtok(NULL, ",");
            }
        }

        fseek(inputFile, busScheduleLocation, SEEK_SET);

        int modulii[busCount];
        int residues[busCount];
        int busIndex = 0;
        int position = 0;

        if (fscanf(inputFile, "%s", busSchedule)) {
            char *busId = strtok(busSchedule, ",");

            while (busId) {
                if (*busId != 'x') {
                    modulii[busIndex] = atoi(busId);
                    residues[busIndex] = modulii[busIndex] - position;

                    ++busIndex;
                }

                ++position;

                busId = strtok(NULL, ",");
            }
        }

        fclose(inputFile);

        printf("%lld", chineseRemainder(modulii, residues, busCount));
    }

    return 0;
}

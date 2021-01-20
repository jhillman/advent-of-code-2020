/* Day 25, part 1 = 354320 */

#include <stdio.h>
#include <stdlib.h>

int getLoopSize(int publicKey, int subjectNumber) {
    int value = 1;
    int loopSize = 0;

    while (value != publicKey) {
        ++loopSize;

        value *= subjectNumber;
        value %= 20201227;
    }

    return loopSize;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char *line = (char *) malloc(10 * sizeof(char));
        size_t length;

        getline(&line, &length, inputFile);

        int cardPublicKey = atoi(line);

        getline(&line, &length, inputFile);

        int doorPublicKey = atoi(line);

        fclose(inputFile);
        free(line);

        int cardLoopSize = getLoopSize(cardPublicKey, 7);
        long encryptionKey = 1;

        for (int i = 0; i < cardLoopSize; i++) {
            encryptionKey *= doorPublicKey;
            encryptionKey %= 20201227;
        }

        printf("%ld", encryptionKey);
    }

    return 0;
}

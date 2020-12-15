/* Day 14, part 2 = ? */

#include <stdio.h>
#include "computer.h"

int main() {
    struct Computer *computer = getComputer();

    if (computer) {
        char mask[MASK_LENGTH + 1];
        long bit;
        long floatingBitCount;
        long floatingBits;
        char *maskPtr;
        long memoryOffset;
        long value;

        long memorySum = 0;

        for (int i = 0; i < computer->instructionCount; i++) {
            if (i == 0) {
                printf("here\n");
                strcpy(mask, "000000000000000000000000000000X1001X");
            }
            switch (computer->instructions[i].type) {
                case MASK:
                    strcpy(mask, computer->instructions[i].mask);
                    break;
                case MEMORY:
                    bit = 1;
                    floatingBitCount = 0;
                    floatingBits = 0;
                    maskPtr = mask + MASK_LENGTH - 1;
                    memoryOffset = computer->instructions[i].memoryOffset;
                    value = computer->instructions[i].value;

                    while (maskPtr >= mask) {
                        if (*maskPtr == '1' && (value & bit) == 0) {
                            memoryOffset += bit;
                        } else if (*maskPtr == 'X') {
                            ++floatingBitCount;
                            floatingBits += bit;
                        }

                        --maskPtr;
                        bit <<= 1;
                    }

                    long floatingBitOptions = 1LL << floatingBitCount;

                    printf("%ld, %ld, %ld\n", floatingBitCount, floatingBits, floatingBitOptions);

                    for (int j = 0; j < floatingBitOptions; j++) {
                        long long floatingMemoryOffset = memoryOffset;
                        bit = 1;

                        for (int k = 0; k < floatingBitCount; k++) {
                            while ((bit & floatingBits) != bit) {
                                bit <<= 1;
                            }

                            printf("bit: %ld\n", bit);

                            if ((j & bit) == bit) {
                                floatingMemoryOffset += bit;
                            } else if ((j & bit) == j) {
                                floatingMemoryOffset -= bit;
                            }

                            bit <<= 1;
                        }

                        printf("memory offset: %lld\n", floatingMemoryOffset);

                        memorySum -= computer->memory[floatingMemoryOffset];
                        memorySum += value;

                        computer->memory[floatingMemoryOffset] = value;
                    }
                    break;
            }
        }

        freeComputer(computer);

        printf("%ld", memorySum);
    }

    return 0;
}

/* Day 5, part 1 = 901 */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *passesFile = fopen("passes.txt", "r");

    if (!passesFile) {
        passesFile = fopen("../passes.txt", "r");
    }

    if (passesFile) {
        char passLine[40];
        char passLineLength;
        int highestSeatId = 0;

        while (fgets(passLine, sizeof(passLine), passesFile)) {
            int rowBit = 64;
            int seatBit = 4;
            int row = 0;
            int seat = 0;

            for (int i = 0; i < 7; i++) {
                if (passLine[i] == 'B') {
                    row += rowBit;
                }

                rowBit >>= 1;
            }

            for (int i = 7; i < 10; i++) {
                if (passLine[i] == 'R') {
                    seat += seatBit;
                }

                seatBit >>= 1;
            }

            int seatId = row * 8 + seat;

            if (seatId > highestSeatId) {
                highestSeatId = seatId;
            }
        }

        fclose(passesFile);

        printf("%d", highestSeatId);
    }

    return 0;
}
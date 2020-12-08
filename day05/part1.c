/* Day 5, part 1 = 901 */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char passLine[40];
        char passLineLength;
        int highestSeatId = 0;

        while (fgets(passLine, sizeof(passLine), inputFile)) {
            int rowMin = 0;
            int rowMax = 127;
            int seatMin = 0;
            int seatMax = 7;
            int seatId;
            
            for (int i = 0; i < 10; i++) {
                switch (passLine[i]) {
                    case 'F':
                        rowMax = rowMin + (rowMax - rowMin) / 2;
                        break;
                    case 'B':
                        rowMin = rowMax - (rowMax - rowMin) / 2;
                        break;
                    case 'L':
                        seatMax = seatMin + (seatMax - seatMin) / 2;
                        break;
                    case 'R':
                        seatMin = seatMax - (seatMax - seatMin) / 2;
                        break;
                }

                seatId = rowMin * 8 + seatMin;

                if (seatId > highestSeatId) {
                    highestSeatId = seatId;
                }
            }
        }

        fclose(inputFile);

        printf("%d", highestSeatId);
    }

    return 0;
}
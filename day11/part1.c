/* Day 11, part 1 = 2289 */

#include <stdio.h>
#include "seats.h"

int occupiedSeatCount(char **seatLayout, int rowCount, int columnCount, int row, int column) {
    int occupiedSeatCount = 0;

    int minRow = row > 1 ? row - 1 : 0;
    int maxRow = row < rowCount - 1 ? row + 1 : rowCount - 1;
    int minColumn = column > 1 ? column - 1 : 0;
    int maxColumn = column < columnCount - 1 ? column + 1 : columnCount - 1;

    for (int i = minRow; i <= maxRow; i++) {
        for (int j = minColumn; j <= maxColumn; j++) {
            if (!(i == row && j == column) && seatLayout[i][j] == '#') {
                ++occupiedSeatCount;
            }
        }
    }

    return occupiedSeatCount;
}

int main() {
    int rowCount;
    int columnCount;
    char **seatLayout = getSeatLayout(&rowCount, &columnCount);

    if (seatLayout) {
        while (applyRules(seatLayout, rowCount, columnCount, 4));

        int count = totalOccupiedSeatCount(seatLayout, rowCount, columnCount);

        freeLayout(seatLayout, rowCount);

        printf("%d", count);
    }

    return 0;
}

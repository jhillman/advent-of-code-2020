/* Day 11, part 2 = 2059 */

#include <stdio.h>
#include "seats.h"

struct SeatTraverser {
    int rowDelta;
    int columnDelta;
};

int occupiedSeatCount(char **seatLayout, int rowCount, int columnCount, int row, int column) {
    struct SeatTraverser seatTraversers[] = {
        { -1, 0 },
        { 1, 0 },
        { 0, -1 },
        { 0, 1 },
        { -1, -1 },
        { 1, -1 },
        { -1, 1 },
        { 1, 1 }
    };

    int occupiedSeatCount = 0;

    for (int i = 0; i < 8; i++) {
        struct SeatTraverser seatTraverser = seatTraversers[i];

        int rowIndex = row + seatTraverser.rowDelta;
        int columnIndex = column + seatTraverser.columnDelta;
        int keepLooking = 1;

        while (keepLooking && rowIndex >= 0 && rowIndex < rowCount && columnIndex >= 0 && columnIndex < columnCount) {
            switch (seatLayout[rowIndex][columnIndex]) {
                case '#':
                    ++occupiedSeatCount;
                    keepLooking = 0;
                    break;
                case '.':
                    rowIndex += seatTraverser.rowDelta;
                    columnIndex += seatTraverser.columnDelta;
                    break;
                case 'L':
                    keepLooking = 0;
                    break;
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
        while (applyRules(seatLayout, rowCount, columnCount, 5));

        int count = totalOccupiedSeatCount(seatLayout, rowCount, columnCount);

        freeLayout(seatLayout, rowCount);

        printf("%d", count);
    }

    return 0;
}

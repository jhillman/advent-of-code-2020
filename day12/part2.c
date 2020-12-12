/* Day 12, part 2 = 39446 */

#include <stdio.h>
#include <stdlib.h>

enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        enum Direction direction = EAST;
        int shipEast = 0;
        int shipNorth = 0;
        int waypointEast = 10;
        int waypointNorth = 1;

        char instruction;
        int value;
        char ch;

        while (fscanf(inputFile, "%c%d%c", &instruction, &value, &ch) >= 2) {
            switch (instruction) {
                case 'N':
                    waypointNorth += value;
                    break;
                case 'S':
                    waypointNorth -= value;
                    break;
                case 'E':
                    waypointEast += value;
                    break;
                case 'W':
                    waypointEast -= value;
                    break;
                case 'L':
                    for (int i = 0; i < value / 90; i++) {
                        int temp = waypointEast;
                        waypointEast = -waypointNorth;
                        waypointNorth = temp;
                    }
                    break;
                case 'R':
                    for (int i = 0; i < value / 90; i++) {
                        int temp = waypointEast;
                        waypointEast = waypointNorth;
                        waypointNorth = -temp;
                    }
                    break;
                case 'F':
                    shipEast += (value * waypointEast);
                    shipNorth += (value * waypointNorth);
                    break;                    
            }
        }

        fclose(inputFile);

        printf("%d", abs(shipNorth) + abs(shipEast));
    }

    return 0;
}

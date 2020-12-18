#include <stdlib.h>
#include <string.h>

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

struct Space {
    int width;
    int height;
    int depth;
    int spissitude;
    int fourDimensions;
    char ****cubes;
};

struct Space *initializeSpace(int width, int height, int depth, int spissitude) {
    struct Space *space = (struct Space *) calloc(1, sizeof(struct Space));
    space->width = width;
    space->height = height;
    space->depth = depth;
    space->spissitude = max(spissitude, 1);
    space->fourDimensions = spissitude > 0;

    space->cubes = (char ****) calloc(space->spissitude, sizeof(char ****));

    for (int w = 0; w < space->spissitude; w++) {
        space->cubes[w] = (char ***) calloc(space->depth, sizeof(char ***));

        for (int z = 0; z < space->depth; z++) {
            space->cubes[w][z] = (char **) calloc(space->height, sizeof(char **));
    
            for (int y = 0; y < space->height; y++) {
                space->cubes[w][z][y] = (char *) calloc(space->width + 1, sizeof(char));
                memset(space->cubes[w][z][y], '.', space->width);
             }
        }
    }

    return space;
}

struct Space *readSpace(int fourDimensions) {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char ch = fgetc(inputFile);
        int width = 0;
        int height = 0;

        while (ch != '\n') {
            ++width;
            ch = fgetc(inputFile);
        }

        fseek(inputFile, 0, SEEK_SET);

        while (!feof(inputFile)) {
            ch = fgetc(inputFile);

            if (ch == '\n') {
                ++height;
            }
        }

        ++height;

        struct Space *space = initializeSpace(width, height, 1, fourDimensions ? 1 : 0);

        fseek(inputFile, 0, SEEK_SET);

        int y = 0;

        while (y < space->height) {
            fscanf(inputFile, "%s", space->cubes[0][0][y++]);
        }

        fclose(inputFile);

        return space;
    }

    return NULL;
}

void printSpace(struct Space *space) {
    for (int w = 0; w < space->spissitude; w++) {
        for (int z = 0; z < space->depth; z++) {
            printf("z: %d, w: %d\n", z, w);

            for (int y = 0; y < space->height; y++) {
                printf("%s\n", space->cubes[w][z][y]);
            }    

            printf("\n");
        }
    }

    printf("\n");
}

void freeSpace(struct Space *space) {
    for (int w = 0; w < space->spissitude; w++) {
        for (int z = 0; z < space->depth; z++) {
            for (int y = 0; y < space->height; y++) {
                free(space->cubes[w][z][y]);
            }

            free(space->cubes[w][z]);
        }

        free(space->cubes[w]);
    }

    free(space->cubes);
    free(space);
}

char cubeState(struct Space *space, int x, int y, int z, int w) {
    int activeNeighborCount = 0;
    char state = '.';

    for (int nW = max(0, w - 1); nW <= min(space->spissitude - 1, w + 1); nW++) {
        for (int nZ = max(0, z - 1); nZ <= min(space->depth - 1, z + 1); nZ++) {
            for (int nY = max(0, y - 1); nY <= min(space->height - 1, y + 1); nY++) {
                for (int nX = max(0, x - 1); nX <= min(space->width - 1, x + 1); nX++) {
                    if (!(nW == w && nZ == z && nY == y && nX == x)) {
                        if (space->cubes[nW][nZ][nY][nX] == '#') {
                            ++activeNeighborCount;
                        }
                    }
                }    
            }
        }
    }    

    switch (space->cubes[w][z][y][x]) {
        case '#':
            if (activeNeighborCount == 2 || activeNeighborCount == 3) {
                state = '#';
            }
            break;
        case '.':
            if (activeNeighborCount == 3) {
                state = '#';
            }
            break;
    }

    return state;
}

struct Space *cycleSpace(struct Space *space) {
    struct Space *expandedSpace = initializeSpace(
        space->width + 2, 
        space->height + 2, 
        space->depth + 2,
        space->fourDimensions ? space->spissitude + 2 : 0);

    int wOffset = space->fourDimensions ? 1 : 0;

    for (int w = 0; w < space->spissitude; w++) {
        for (int z = 0; z < space->depth; z++) {
            for (int y = 0; y < space->height; y++) {
                for (int x = 0; x < space->width; x++) {
                    expandedSpace->cubes[w + wOffset][z + 1][y + 1][x + 1] = space->cubes[w][z][y][x];
                }    
            }
        }    
    }

    struct Space *cycledSpace = initializeSpace(
        space->width + 2, 
        space->height + 2, 
        space->depth + 2,
        space->fourDimensions ? space->spissitude + 2 : 0);

    for (int w = 0; w < cycledSpace->spissitude; w++) {
        for (int z = 0; z < cycledSpace->depth; z++) {
            for (int y = 0; y < cycledSpace->height; y++) {
                for (int x = 0; x < cycledSpace->width; x++) {
                    cycledSpace->cubes[w][z][y][x] = cubeState(expandedSpace, x, y, z, w);
                }    
            }    
        }
    }

    freeSpace(expandedSpace);
    freeSpace(space);

    return cycledSpace;
}

int activeCubeCount(struct Space *space) {
    int activeCount = 0;

    for (int w = 0; w < space->spissitude; w++) {
        for (int z = 0; z < space->depth; z++) {
            for (int y = 0; y < space->height; y++) {
                for (int x = 0; x < space->width; x++) {
                    if (space->cubes[w][z][y][x] == '#') {
                        ++activeCount;
                    }
                }    
            }    
        }
    }

    return activeCount;
}

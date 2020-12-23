/* Day 20, part 1 = 16192267830719 */

#include <stdio.h>
#include "tiles.h"

int main() {
    struct TileData *data = getTileData();

    if (data) {
        long product = 1;

        for (int i = 0; i < data->tileCount; i++) {
            int verticalMatchCount = 0;
            int lastVertcialMatch = -1;

            for (int j = 0; j < data->verticalEdgeMatchCount; j++) {
                if (data->verticalEdgeMatches[j].tile1.id == data->tiles[i].id) {
                    if (data->verticalEdgeMatches[j].tile2.id != lastVertcialMatch) {
                        ++verticalMatchCount;
                    }

                    lastVertcialMatch = data->verticalEdgeMatches[j].tile2.id;
                }
            }

            if (verticalMatchCount == 2) {
                product *= data->tiles[i].id;
            }
        }

        freeTileData(data);

        printf("%ld", product);
    }

    return 0;
}

/* Day 22, part 1 = 32677 */

#include <stdio.h>
#include "cards.h"

int main() {
    struct GameData *data = readGameData();

    if (data) {
        if (playGame(data->playerOneDeck, data->playerTwoDeck, false) == 1) {
            printf("%d", deckScore(data->playerOneDeck));
        } else {
            printf("%d", deckScore(data->playerTwoDeck));
        }

        freeDeck(data->playerOneDeck);
        freeDeck(data->playerTwoDeck);
        free(data);
    }

    return 0;
}

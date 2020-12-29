#include <stdlib.h>
#include <stdbool.h>

struct Card {
    int value;
    struct Card *next;
};

struct Deck {
    struct Card *top;
    struct Card *bottom;
    int count;
};

struct Round {
    struct Deck *playerOneDeck;
    struct Deck *playerTwoDeck;
};

struct GameData {
    struct Deck *playerOneDeck;
    struct Deck *playerTwoDeck;
};

void addCard(struct Deck *deck, int value) {
    struct Card *card = (struct Card *) calloc(1, sizeof(struct Card));
    card->value = value;

    if (deck->bottom) {
        deck->bottom->next = card;
        deck->bottom = card;
    } else {
        deck->top = deck->bottom = card;
    }

    ++deck->count;
}

int drawCard(struct Deck *deck) {
    struct Card *card = deck->top;
    int value = card->value;

    deck->top = card->next;
    free(card);

    if (--deck->count == 0) {
        deck->top = deck->bottom = NULL;
    }

    return value;
}

bool decksEqual(struct Deck *deck1, struct Deck *deck2) {
    bool equal = false;

    if (deck1->count == deck2->count) {
        equal = true;
        struct Card *card1 = deck1->top;
        struct Card *card2 = deck2->top;

        for (int i = 0; equal && i < deck1->count; i++) {
            equal = card1->value == card2->value;

            card1 = card1->next;
            card2 = card2->next;
        }
    }

    return equal;
}

struct Deck *copyDeck(struct Deck *deck, int depth) {
    struct Deck *deckCopy = (struct Deck *) calloc(1, sizeof(struct Deck));
    struct Card *card = deck->top;

    for (int i = 0; i < depth; i++) {
        addCard(deckCopy, card->value);

        card = card->next;
    }

    return deckCopy;
}

void freeDeck(struct Deck *deck) {
    if (deck) {
        while (deck->count) {
            drawCard(deck);
        }

        free(deck);
    }
}

int playGame(struct Deck *playerOneDeck, struct Deck *playerTwoDeck, bool recursive) {
    struct Round *rounds = NULL;
    int roundCount = 0;
    bool duplicateFound = false;

    while (!duplicateFound && playerOneDeck->count && playerTwoDeck->count) {
        for (int i = 0; !duplicateFound && i < roundCount; i++) {
            if (decksEqual(rounds[i].playerOneDeck, playerOneDeck) && decksEqual(rounds[i].playerTwoDeck, playerTwoDeck)) {
                duplicateFound = true;
            }
        }

        if (!duplicateFound) {
            if (++roundCount > 1) {
               rounds = (struct Round *) realloc(rounds, roundCount * sizeof(struct Round));
            } else {
               rounds = (struct Round *) malloc(roundCount * sizeof(struct Round));
            }

            rounds[roundCount - 1] = (struct Round) { copyDeck(playerOneDeck, playerOneDeck->count), copyDeck(playerTwoDeck, playerTwoDeck->count) };

            int playerOneCard = drawCard(playerOneDeck);
            int playerTwoCard = drawCard(playerTwoDeck);

            if (recursive && playerOneCard <= playerOneDeck->count && playerTwoCard <= playerTwoDeck->count) {
                struct Deck *playerOneDeckCopy = copyDeck(playerOneDeck, playerOneCard);
                struct Deck *playerTwoDeckCopy = copyDeck(playerTwoDeck, playerTwoCard);

                if (playGame(playerOneDeckCopy, playerTwoDeckCopy, true) == 1) {
                    addCard(playerOneDeck, playerOneCard);
                    addCard(playerOneDeck, playerTwoCard);
                } else {
                    addCard(playerTwoDeck, playerTwoCard);
                    addCard(playerTwoDeck, playerOneCard);
                }

                freeDeck(playerOneDeckCopy);
                freeDeck(playerTwoDeckCopy);
            } else if (playerOneCard > playerTwoCard) {
                addCard(playerOneDeck, playerOneCard);
                addCard(playerOneDeck, playerTwoCard);
            } else {
                addCard(playerTwoDeck, playerTwoCard);
                addCard(playerTwoDeck, playerOneCard);
            }
        }
    }

    if (rounds) {
        for (int i = 0; i < roundCount; i++) {
            freeDeck(rounds[i].playerOneDeck);
            freeDeck(rounds[i].playerTwoDeck);
        }

        free(rounds);
    }

    if (duplicateFound || playerOneDeck->count > playerTwoDeck->count) {
        return 1;
    } else {
        return 2;
    }
}

int deckScore(struct Deck *deck) {
    int score = 0;

    while (deck->count) {
        score += deck->count * drawCard(deck);
    }

    return score;
}

struct GameData *readGameData() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char *line;
        size_t length;
        int number;
        struct Deck *deck;

        struct GameData *data = (struct GameData *) calloc(1, sizeof(struct GameData));

        data->playerOneDeck = (struct Deck *) calloc(1, sizeof(struct Deck));
        data->playerTwoDeck = (struct Deck *) calloc(1, sizeof(struct Deck));

        while(getline(&line, &length, inputFile) != -1) {
            if (sscanf(line, "Player %d:", &number)) {
                if (number == 1) {
                    deck = data->playerOneDeck;
                } else {
                    deck = data->playerTwoDeck;
                }
            } else if (sscanf(line, "%d", &number) == 1) {
                addCard(deck, number);
            }
        }
        
        fclose(inputFile);

        return data;
    }

    return NULL;
}
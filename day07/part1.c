/* Day 7, part 1 = 119 */

#include <stdio.h>
#include "bags.h"

int bagCanContain(struct Rule ruleLookUp[WAVY - BRIGHT + 1][YELLOW - AQUA + 1], struct Bag bag, enum Modifier modifier, enum Color color) {
    struct Rule rule = ruleLookUp[bag.modifier][bag.color];
    int canContain = 0;

    if (rule.canContain) {
        canContain = 1;
    } else if (bag.modifier == modifier && bag.color == color) {
        ruleLookUp[bag.modifier][bag.color].canContain = 1;

        canContain = 1;
    } else if (rule.bagCount > 0) {
        for (int i = 0; !canContain && i < rule.bagCount; i++) {
            canContain = bagCanContain(ruleLookUp, rule.bags[i], modifier, color);
        }
    }

    return canContain;
}

int main() {
    struct RuleData data = readInput();

    if (data.ruleCount > 0) {
        int bagCount = 0;
        enum Modifier modifier = SHINY;
        enum Color color = GOLD;

        for (int i = 0; i < data.ruleCount; i++) {
            struct Rule rule = data.rules[i];

            if (rule.bag.modifier == modifier && rule.bag.color == color) {
                continue;
            }

            if (bagCanContain(data.ruleLookUp, rule.bag, modifier, color)) {
                ++bagCount;
            }
        }

        freeData(data);

        printf("%d", bagCount);
    }

    return 0;
}

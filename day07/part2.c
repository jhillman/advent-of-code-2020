/* Day 7, part 2 = 155802 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bags.h"

int bagCount(struct Rule ruleLookUp[WAVY - BRIGHT + 1][YELLOW - AQUA + 1], struct Bag bag, enum Modifier modifier, enum Color color) {
    struct Rule rule = ruleLookUp[bag.modifier][bag.color];
    int count = 0;

    if (rule.bagCount > 0) {
        for (int i = 0; i < rule.bagCount; i++) {
            count += rule.bags[i].count;
            count += rule.bags[i].count * bagCount(ruleLookUp, rule.bags[i], modifier, color);
        }
    }

    return count;
}

int main() {
    struct RuleData data = readInput();

    if (data.ruleCount > 0) {
        enum Modifier modifier = SHINY;
        enum Color color = GOLD;
        struct Rule rule = data.ruleLookUp[modifier][color];

        int totalBagCount = bagCount(data.ruleLookUp, rule.bag, modifier, color);

        freeData(data);

        printf("%d", totalBagCount);
    }

    return 0;
}

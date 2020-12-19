/* Day 19, part 2 = 392 */

#include <stdio.h>
#include "rules.h"

int main() {
    struct RulesData *data = readRulesData();

    if (data) {
        char ruleString[20];

        strcpy(ruleString, "42 | 42 8");
        parseRule(8, ruleString, data->rules);

        strcpy(ruleString, "42 31 | 42 11 31");
        parseRule(11, ruleString, data->rules);

        int validCount = validInputCount(data);

        freeRulesData(data);

        printf("%d", validCount);
    }

    return 0;
}

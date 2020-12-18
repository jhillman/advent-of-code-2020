/* Day 18, part 2 = 545115449981968 */

#include <stdio.h>
#include "math.h"

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char expression[200];
        long sum = 0;

        while (fgets(expression, sizeof(expression), inputFile)) {
            sum += evaluate(expression, 1).value;
        }

        fclose(inputFile);

        printf("%ld", sum);
    }

    return 0;
}

/* Day 8, part 1 = 1586 */

#include <stdio.h>
#include "boot.h"

int main() {
    struct BootData data = readInput();

    if (data.instructionCount > 0) {
        int offset = 0;
        int accumulator = 0;

        while (1) {
            if (data.instructions[offset].runCount > 0) {
                break;
            }

            data.instructions[offset].runCount++;

            switch (data.instructions[offset].operation) {
                case NOP:
                    ++offset;
                    break;
                case ACC:
                    accumulator += data.instructions[offset].argument;
                    ++offset;
                    break;
                case JMP:
                    offset += data.instructions[offset].argument;
                    break;
            }
        }

        freeData(data);

        printf("%d", accumulator);
    }

    return 0;
}

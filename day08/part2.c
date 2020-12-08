/* Day 8, part 2 = 703 */

#include <stdio.h>
#include "boot.h"

int changeInstruction(struct Instruction *instructions, int instructionCount) {
    int changedInstructionIndex = 0;

    for (int i = 0; i < instructionCount; i++) {
        if (instructions[i].operation != ACC && !instructions[i].changed) {
            instructions[i].changed = 1;

            if (instructions[i].operation == NOP) {
                instructions[i].operation = JMP;
            } else {
                instructions[i].operation = NOP;
            }

            changedInstructionIndex = i;
            break;
        }
    }

    return changedInstructionIndex;
}

int main() {
    struct BootData data = readInput();

    if (data.instructionCount > 0) {
        int offset = 0;
        int accumulator = 0;
        int changedInstructionIndex = changeInstruction(data.instructions, data.instructionCount);

        while (1) {
            if (offset >= data.instructionCount) {
                break;
            }

            if (data.instructions[offset].runCount > 0) {
                for (int i = 0; i < data.instructionCount; i++) {
                    data.instructions[i].runCount = 0;
                }

                if (data.instructions[changedInstructionIndex].operation == NOP) {
                    data.instructions[changedInstructionIndex].operation = JMP;
                } else {
                    data.instructions[changedInstructionIndex].operation = NOP;
                }

                changedInstructionIndex = changeInstruction(data.instructions, data.instructionCount);

                offset = 0;
                accumulator = 0;

                continue;
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

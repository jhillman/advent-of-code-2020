/* Day 16, part 2 = 2766491048287 */

#include <stdio.h>
#include "tickets.h"

int main() {
    struct TicketData *data = getTicketData();

    if (data) {
        int ***ticketValidValueMatrices = (int ***) calloc(data->nearbyCount, sizeof(int ***));

        for (int i = 0; i < data->nearbyCount; i++) {
            ticketValidValueMatrices[i] = (int **) calloc(data->ruleCount, sizeof(int **));

            for (int j = 0; j < data->ruleCount; j++) {
                ticketValidValueMatrices[i][j] = (int *) calloc(data->valueCount, sizeof(int));

                if (data->nearby[i].valid) {
                    for (int k = 0; k < data->valueCount; k++) {
                        ticketValidValueMatrices[i][j][k] = valueValidForRule(data->nearby[i].values[k].value, data->rules[j]);
                    }
                }
            }
        }

        int **overlayedValueMatrix = (int **) calloc(data->ruleCount, sizeof(int **));

        for (int i = 0; i < data->ruleCount; i++) {
            overlayedValueMatrix[i] = (int *) calloc(data->valueCount, sizeof(int));

            for (int j = 0; j < data->valueCount; j++) {
                overlayedValueMatrix[i][j] = 1;
            }
        }

        for (int i = 0; i < data->nearbyCount; i++) {
            for (int j = 0; j < data->ruleCount; j++) {
                for (int k = 0; k < data->valueCount; k++) {
                    if (data->nearby[i].valid) {
                        overlayedValueMatrix[j][k] &= ticketValidValueMatrices[i][j][k];
                    }
                }
            }
        }

        int assignedValues = 0;

        while (assignedValues < data->valueCount) {
            for (int i = 0; i < data->valueCount; i++) {
                int oneCount = 0;
                int index = -1;

                for (int j = 0; j < data->ruleCount; j++) {
                    if (data->rules[j].valueIndex < 0 && overlayedValueMatrix[j][i]) {
                        ++oneCount;
                        index = j;
                    }
                }

                if (oneCount == 1) {
                    data->rules[index].valueIndex = i;
                    ++assignedValues;

                    for (int j = 0; j < data->valueCount; j++) {
                        overlayedValueMatrix[index][j] = 0;
                    }

                    break;
                }
            }
        }

        long departureValues = 1;

        for (int i = 0; i < data->ruleCount; i++) {
            if (strstr(data->rules[i].name, "departure")) {
                departureValues *= data->mine.values[data->rules[i].valueIndex].value;
            }
        }

        for (int i = 0; i < data->nearbyCount; i++) {
            for (int j = 0; j < data->valueCount; j++) {
                free(ticketValidValueMatrices[i][j]);
            }

            free(ticketValidValueMatrices[i]);
        }

        free(ticketValidValueMatrices);

        for (int i = 0; i < data->valueCount; i++) {
            free(overlayedValueMatrix[i]);
        }

        free(overlayedValueMatrix);

        freeTicketData(data);

        printf("%ld", departureValues);
    }

    return 0;
}

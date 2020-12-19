#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Rule {
    char character;
    int *sequence;
    int **alternates;
};

struct CurrentRule {
    int number;
    struct CurrentRule *next;
};

struct RulesData {
    struct Rule *rules;
    int ruleCount;
    FILE *inputFile;
};

bool matchesRule(char *input, struct CurrentRule *currentRule, struct Rule *rules);
void freeRule(struct Rule *rule);
void freeCurrentRule(struct CurrentRule *currentRule);

bool matchesSequence(char *input, int *sequence, struct CurrentRule *currentRule, struct Rule *rules) {
    struct CurrentRule *sequenceRule =  (struct CurrentRule *) calloc(1, sizeof(struct CurrentRule *));
    struct CurrentRule *currentSequenceRule = sequenceRule;

    for (int i = 0; i < *sequence; i++) {
        if (i > 0) {
            currentSequenceRule->next = (struct CurrentRule *) calloc(1, sizeof(struct CurrentRule *));
            currentSequenceRule = currentSequenceRule->next;
        }

        currentSequenceRule->number = sequence[i + 1];
    }

    currentSequenceRule->next = currentRule;

    return matchesRule(input, sequenceRule, rules);
}

struct CurrentRule *copyCurrentRule(struct CurrentRule *currentRule) {
    struct CurrentRule *currentRuleCopy = NULL;

    if (currentRule) {
        currentRuleCopy = (struct CurrentRule *) calloc(1, sizeof(struct CurrentRule *));
        currentRuleCopy->number = currentRule->number;

        currentRuleCopy->next = copyCurrentRule(currentRule->next);
    }

    return currentRuleCopy;
}

bool matchesRule(char *input, struct CurrentRule *currentRule, struct Rule *rules) {
    if (strlen(input) == 0 && !currentRule) {
        return true;
    }

    if (strlen(input) == 0 || !currentRule) {
        freeCurrentRule(currentRule);

        return false;
    }

    struct Rule rule = rules[currentRule->number];
    struct CurrentRule *nextRule = currentRule->next;

    free(currentRule);

    if (rule.sequence) {
        return matchesSequence(input, rule.sequence, nextRule, rules);
    } else if (rule.alternates) {
        bool alternatesMatch = false;

        for (int i = 0; !alternatesMatch && i < **rule.alternates; i++) {
            alternatesMatch = matchesSequence(input, rule.alternates[i + 1], copyCurrentRule(nextRule), rules);
        }

        freeCurrentRule(nextRule);

        return alternatesMatch;
    } else {
        if (*input == rule.character) {
            return matchesRule(input + 1, nextRule, rules);
        } else {
            return false;            
        }
    }

    return false;
}

int *parseSequence(char *rule) {
    char ruleCopy[32];
    
    strcpy(ruleCopy, rule);
    char *rulePart = strtok(ruleCopy, " ");
    int sequenceLength = 0;

    while (rulePart) {
        ++sequenceLength;

        rulePart = strtok(NULL, " ");
    }

    int *sequence = (int *) calloc(sequenceLength + 1, sizeof(int));
    *sequence = sequenceLength;

    strcpy(ruleCopy, rule);
    rulePart = strtok(ruleCopy, " ");

    int sequenceIndex = 1;

    while (rulePart) {
        sequence[sequenceIndex++] = atoi(rulePart);

        rulePart = strtok(NULL, " ");
    }

    return sequence;
}

int **parseAlternates(char *rule) {
    char ruleCopy[32];
    
    strcpy(ruleCopy, rule);
    char *rulePart = strtok(ruleCopy, "|");
    int *alternateCount = (int *) calloc(1, sizeof(int));
    *alternateCount = 0;

    while (rulePart) {
        ++*alternateCount;

        rulePart = strtok(NULL, "|");
    }

    int **alternates = (int **) calloc(*alternateCount + 1, sizeof(int **));
    *alternates = alternateCount;

    strcpy(ruleCopy, rule);
    rulePart = strtok(ruleCopy, "|");

    char ruleParts[*alternateCount][16];
    int rulePartIndex = 0;

    while (rulePart) {
        while (*rulePart == ' ') {
            ++rulePart;
        }

        strcpy(ruleParts[rulePartIndex++], rulePart);

        rulePart = strtok(NULL, "|");
    }

    int alternatesIndex = 0;

    while (alternatesIndex < *alternateCount) {
        alternates[alternatesIndex + 1] = parseSequence(ruleParts[alternatesIndex]);

        ++alternatesIndex;
    }

    return alternates;
}

void parseRule(int number, char *ruleString, struct Rule *rules) {
    freeRule(&rules[number]);

    if (strstr(ruleString, "\"")) {
        rules[number].character = *(ruleString + 1);
    } else if (strstr(ruleString, "|")) {
        rules[number].alternates = parseAlternates(ruleString);
    } else {
        rules[number].sequence = parseSequence(ruleString);
    }
}

struct RulesData *readRulesData() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        struct RulesData *data = (struct RulesData *) calloc(1, sizeof(struct RulesData));
        data->ruleCount = 0;

        char line[100];

        while (fgets(line, sizeof(line), inputFile) && strstr(line, ":")) {
            ++data->ruleCount;
        }

        fseek(inputFile, 0, SEEK_SET);

        data->rules = (struct Rule *) calloc(data->ruleCount, sizeof(struct Rule));
        data->inputFile = inputFile;

        int number;
        char *ruleString;
        char *rulePart;

        while (fgets(line, sizeof(line), inputFile) && (ruleString = strstr(line, ":"))) {
            sscanf(line, "%d", &number);
            ruleString += 2;

            parseRule(number, ruleString, data->rules);
        }

        return data;
    }

    return NULL;
}

int validInputCount(struct RulesData *data) {
    int validCount = 0;
    char input[100];

    while (fgets(input, sizeof(input), data->inputFile)) {
        int inputLength = strlen(input);

        if (input[inputLength - 1] == '\n') {
            input[inputLength - 1] = '\0';
        }

        struct CurrentRule *currentRule = (struct CurrentRule *) calloc(1, sizeof(struct CurrentRule *));
        currentRule->number = 0;

        if (matchesRule(input, currentRule, data->rules)) {
            ++validCount;
        }
    }

    return validCount;
}

void freeRule(struct Rule *rule) {
    if (rule->sequence) {
        free(rule->sequence);

        rule->sequence = NULL;
    } else if (rule->alternates) {
        for (int i = 0; i < **rule->alternates; i++) {
            free(rule->alternates[i + 1]);                
        }

        free(rule->alternates);
        rule->alternates = NULL;
    }
}

void freeCurrentRule(struct CurrentRule *currentRule) {
    if (currentRule) {
        freeCurrentRule(currentRule->next);

        free(currentRule);
    }
}

void freeRulesData(struct RulesData *data) {
    fclose(data->inputFile);

    for (int i = 0; i < data->ruleCount; i++) {
        freeRule(&data->rules[i]);
    }

    free(data->rules);
    free(data);
}
struct ExpressionResult {
    long value;
    int offset;
};

struct ExpressionResult evaluate(char *expression, int advanced) {
    long value;
    long multiplicands[30];
    int multiplicandIndex = 0;
    char *operator = NULL;
    char *expressionStart = expression;

    while (*expression) {
        switch (*expression) {
            case '(':
                if (operator == NULL) {
                    struct ExpressionResult result = evaluate(expression + 1, advanced);

                    value = result.value;

                    expression += result.offset;
                } else {
                    struct ExpressionResult result = evaluate(expression + 1, advanced);

                    switch (*operator) {
                        case '+':
                            value = value + result.value;
                            break;
                        case '*':
                            if (advanced) {
                                multiplicands[multiplicandIndex++] = value;
                                value = result.value;
                            } else {
                                value = value * result.value;
                            }
                            break;
                    }

                    operator = NULL;
                    expression += result.offset;
                }
                break;
            case ')':
                for (int i = 0; i < multiplicandIndex; i++) {
                    value *= multiplicands[i];
                }

                return (struct ExpressionResult) { value, expression - expressionStart + 1 };
            case '+':
            case '*':
                operator = expression;
                break;
            default:
                if (operator == NULL) {
                    value = *expression - '0';
                } else {
                    switch (*operator) {
                        case '+':
                            value = value + (*expression - '0');
                            break;
                        case '*':
                            if (advanced) {
                                multiplicands[multiplicandIndex++] = value;
                                value = (*expression - '0');
                            } else {
                                value = value * (*expression - '0');
                            }
                            break;
                    }

                    operator = NULL;
                }
                break;
        }

        ++expression;

        while (*expression == ' ' || *expression == '\n') {
            ++expression;
        }
    }

    for (int i = 0; i < multiplicandIndex; i++) {
        value *= multiplicands[i];
    }

    return (struct ExpressionResult) { value, 0 };
}
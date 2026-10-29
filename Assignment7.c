#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

char postfix[MAX];
int k = 0;

void print_step(char sym) {
    printf("%c ", sym);

    if (top == -1)
        printf("-");

    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);

    postfix[k] = '\0';
    printf(" %s\n", k ? postfix : "-");
}

int icp(char c) {
    if (c == '(')
        return 5;

    if (c == '^')
        return 4;

    if (c == '*' || c == '/' || c == '%')
        return 2;

    if (c == '+' || c == '-')
        return 1;

    return 0;
}

int isp(char c) {
    if (c == '^')
        return 3;

    if (c == '*' || c == '/' || c == '%')
        return 2;

    if (c == '+' || c == '-')
        return 1;

    return 0;
}

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

char pop(void) {
    if (top == -1)
        return '\0';

    return stack[top--];
}

void infix_to_postfix(const char *in) {
    int i;
    char c;

    top = -1;
    k = 0;

    for (i = 0; in[i] != '\0'; i++) {
        c = in[i];

        if (isspace((unsigned char)c))
            continue;

        if (isdigit((unsigned char)c)) {
            postfix[k++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();

            if (top != -1)
                pop();
        } else {
            while (top != -1 && isp(stack[top]) >= icp(c))
                postfix[k++] = pop();

            push(c);
        }

        print_step(c);
    }

    while (top != -1)
        postfix[k++] = pop();

    postfix[k] = '\0';
}

int eval_postfix(const char *p) {
    int values[MAX];
    int valueTop = -1;
    int i, j;
    int a, b, result;

    for (i = 0; p[i] != '\0'; i++) {
        if (isdigit((unsigned char)p[i])) {
            values[++valueTop] = p[i] - '0';
        } else {
            b = values[valueTop--];
            a = values[valueTop--];

            switch (p[i]) {
                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    result = a / b;
                    break;

                case '%':
                    result = a % b;
                    break;

                case '^':
                    result = 1;

                    for (j = 0; j < b; j++)
                        result = result * a;

                    break;

                default:
                    return 0;
            }

            values[++valueTop] = result;
        }
    }

    return values[valueTop];
}

int main(void) {
    char in[MAX];

    if (!fgets(in, sizeof in, stdin))
        return 1;

    in[strcspn(in, "\r\n")] = '\0';

    printf("SYMBOL STACK POSTFIX\n");

    infix_to_postfix(in);

    printf("POSTFIX: %s\n", postfix);
    printf("VALUE: %d\n", eval_postfix(postfix));

    return 0;
}

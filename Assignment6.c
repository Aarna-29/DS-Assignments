#include <stdio.h>
#include <string.h>

#define DEPTH 64
#define LEN 256

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

int is_operand(char c) {
    return (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9');
}

int icp_pre(char c) {
    if (c == '(')
        return 5;
    if (c == '^')
        return 3;
    if (c == '*' || c == '/' || c == '%')
        return 2;
    if (c == '+' || c == '-')
        return 1;

    return 0;
}

int isp_pre(char c) {
    if (c == '^')
        return 4;
    if (c == '*' || c == '/' || c == '%')
        return 2;
    if (c == '+' || c == '-')
        return 1;

    return 0;
}

void infix_to_postfix(const char *in, char *out) {
    char stack[LEN];
    int top = -1;
    int i, k = 0;
    char c;

    for (i = 0; in[i] != '\0'; i++) {
        c = in[i];

        if (is_operand(c)) {
            out[k++] = c;
        }
        else if (c == '(') {
            stack[++top] = c;
        }
        else if (c == ')') {
            while (top >= 0 && stack[top] != '(')
                out[k++] = stack[top--];

            if (top >= 0)
                top--;
        } else {
            while (top >= 0 && stack[top] != '(' &&
                   isp(stack[top]) >= icp(c)) {
                out[k++] = stack[top--];
            }

            stack[++top] = c;
        }
    }

    while (top >= 0)
        out[k++] = stack[top--];

    out[k] = '\0';
}

void infix_to_prefix(const char *in, char *out) {
    char reverse[LEN], result[LEN], stack[LEN];
    int top = -1;
    int i, k = 0;
    int n = strlen(in);
    char c;

    for (i = 0; i < n; i++) {
        c = in[n - 1 - i];

        if (c == '(')
            reverse[i] = ')';
        else if (c == ')')
            reverse[i] = '(';
        else
            reverse[i] = c;
    }

    reverse[n] = '\0';

    for (i = 0; reverse[i] != '\0'; i++) {
        c = reverse[i];

        if (is_operand(c)) {
            result[k++] = c;
        }
        else if (c == '(') {
            stack[++top] = c;
        }
        else if (c == ')') {
            while (top >= 0 && stack[top] != '(')
                result[k++] = stack[top--];

            if (top >= 0)
                top--;
        } else {
            while (top >= 0 && stack[top] != '(' &&
                   isp_pre(stack[top]) > icp_pre(c)) {
                result[k++] = stack[top--];
            }

            stack[++top] = c;
        }
    }

    while (top >= 0)
        result[k++] = stack[top--];

    for (i = 0; i < k; i++)
        out[i] = result[k - 1 - i];

    out[k] = '\0';
}

void postfix_to_infix(const char *in, char *out) {
    char stack[LEN][LEN];
    char left[LEN], right[LEN], result[LEN];
    int top = -1;
    int i;

    for (i = 0; in[i] != '\0'; i++) {
        if (is_operand(in[i])) {
            top++;
            stack[top][0] = in[i];
            stack[top][1] = '\0';
        } else {
            strcpy(right, stack[top--]);
            strcpy(left, stack[top--]);

            strcpy(result, "(");
            strcat(result, left);

            int k = strlen(result);
            result[k] = in[i];
            result[k + 1] = '\0';

            strcat(result, right);
            strcat(result, ")");

            strcpy(stack[++top], result);
        }
    }

    strcpy(out, stack[top]);
}

void postfix_to_prefix(const char *in, char *out) {
    char stack[LEN][LEN];
    char left[LEN], right[LEN], result[LEN];
    int top = -1;
    int i;

    for (i = 0; in[i] != '\0'; i++) {
        if (is_operand(in[i])) {
            top++;
            stack[top][0] = in[i];
            stack[top][1] = '\0';
        } else {
            strcpy(right, stack[top--]);
            strcpy(left, stack[top--]);

            result[0] = in[i];
            result[1] = '\0';

            strcat(result, left);
            strcat(result, right);

            strcpy(stack[++top], result);
        }
    }

    strcpy(out, stack[top]);
}

void prefix_to_infix(const char *in, char *out) {
    char stack[LEN][LEN];
    char left[LEN], right[LEN], result[LEN];
    int top = -1;
    int i;

    for (i = (int)strlen(in) - 1; i >= 0; i--) {
        if (is_operand(in[i])) {
            top++;
            stack[top][0] = in[i];
            stack[top][1] = '\0';
        } else {
            strcpy(left, stack[top--]);
            strcpy(right, stack[top--]);

            strcpy(result, "(");
            strcat(result, left);

            int k = strlen(result);
            result[k] = in[i];
            result[k + 1] = '\0';

            strcat(result, right);
            strcat(result, ")");

            strcpy(stack[++top], result);
        }
    }

    strcpy(out, stack[top]);
}

void prefix_to_postfix(const char *in, char *out) {
    char stack[LEN][LEN];
    char left[LEN], right[LEN], result[LEN];
    int top = -1;
    int i, k;

    for (i = (int)strlen(in) - 1; i >= 0; i--) {
        if (is_operand(in[i])) {
            top++;
            stack[top][0] = in[i];
            stack[top][1] = '\0';
        } else {
            strcpy(left, stack[top--]);
            strcpy(right, stack[top--]);

            strcpy(result, left);
            strcat(result, right);

            k = strlen(result);
            result[k] = in[i];
            result[k + 1] = '\0';

            strcpy(stack[++top], result);
        }
    }

    strcpy(out, stack[top]);
}

int main(void) {
    char cmd[16], e[LEN], out[LEN];

    while (scanf("%15s %255s", cmd, e) == 2) {
        out[0] = '\0';

        if (strcmp(cmd, "IN-POST") == 0)
            infix_to_postfix(e, out);

        else if (strcmp(cmd, "IN-PRE") == 0)
            infix_to_prefix(e, out);

        else if (strcmp(cmd, "POST-IN") == 0)
            postfix_to_infix(e, out);

        else if (strcmp(cmd, "POST-PRE") == 0)
            postfix_to_prefix(e, out);

        else if (strcmp(cmd, "PRE-IN") == 0)
            prefix_to_infix(e, out);

        else if (strcmp(cmd, "PRE-POST") == 0)
            prefix_to_postfix(e, out);

        else
            continue;

        printf("%s %s = %s\n", cmd, e, out);
    }

    return 0;
}

// Bruno Antico Galin 10417318
// Enzo Ribeiro 10418262

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

const char *input;
int pos = 0;
char token;
char postfix[MAX];
int pIndex = 0;
int error = 0;

int evaluate_postfix() {
    int stack[MAX];
    int top = -1;
    for (int i = 0; i < pIndex; i++) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (i < pIndex && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }
            stack[++top] = num;
        } else if (postfix[i] == ' ') {
            continue;
        } else {
            if (top < 1) return 0;
            int b = stack[top--];
            int a = stack[top--];
            switch (postfix[i]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = b ? a / b : 0; break;
                case '%': stack[++top] = b ? a % b : 0; break;
            }
        }
    }
    return stack[0];
}

int main() {
    char expr[MAX];

    printf("Digite a expressao: ");
    fgets(expr, MAX, stdin);
    expr[strcspn(expr, "\n")] = '\0';

    input = expr;
    pos = 0;
    error = 0;
    pIndex = 0;

    if (token != '\0' && token != '\n') error = 1;

    printf("%s => ", expr);
    if (error) {
        printf("Erro Sintatico\n");
    } else {
        postfix[pIndex] = '\0';
    }

    return 0;
}

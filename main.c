#include <stdio.h>
#include "stdlib.h"

typedef enum Errors {
    HEAP_IS_OVERFLOW,
} Errors;

int letterToInt(char letter) {
    switch (letter) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            break;
    }
    return 0;
}

typedef struct Item {
    int number;
    char letter;
    struct Item * next;
} Item;

typedef struct Stack {
    Item * head;
    int numberOfEls;
} Stack;

void StackPut(Stack * stack, char letter, int number) {
    Item * tmp = stack->head;
    stack->head = malloc(sizeof(Item));
    if (stack->head == NULL)
        exit(HEAP_IS_OVERFLOW);
    stack->head->letter = letter;
    stack->head->next = tmp;
    stack->head->number = number;
    stack->numberOfEls++;
}

void StackPop(Stack * stack) {
    if (stack->head == NULL)
        return;

    Item * item = stack->head;
    stack->head = stack->head->next;
    stack->numberOfEls--;
    free(item);
}

Stack * StackInit() {
    Stack * stack = malloc(sizeof(Stack));
    stack->head = NULL;
    stack->numberOfEls = 0;
    return stack;
}

void StackFree(Stack * stack) {
    Item * item = stack->head;
    while (item) {
        Item * tmp = item->next;
        free(item);
        item = tmp;
    }
    free(stack);
}

int StackGetInt(Stack * stack) {
    if (stack->head == NULL)
        return 0;
    int res = stack->head->number;
    StackPop(stack);
    return res;
}
char StackGetLetter(Stack * stack) {
    if (stack->head == NULL)
        return 0;
    char res = stack->head->letter;
    StackPop(stack);
    return res;
}

char intToLetter(int x) {
    if (x < 0)
        return '\0';
    else if (x == 1)
        return 'I';
    else if (x > 1 && x <= 5)
        return 'V';
    else if (x > 5 && x <= 10)
        return 'X';
    else if (x > 10 && x <= 50)
        return 'L';
    else if (x > 50 && x <= 100)
        return 'C';
    else if (x > 100 && x <= 500)
        return 'D';
    else if (x > 500 && x <= 1000)
        return 'M';

    return 'M';
}

int romanToInt(char * s){
    int res = 0;
    int i = 0;
    Stack * stack = StackInit();
    while (s[i]) {
            /*
             * if (letterToInt(stack->head->letter) < letterToInt(s[i])) {
                stack->head->number -= letterToInt(s[i]);
                stack->head->letter = s[i];
            }*/
            int last = 0;
            if (stack->head)
                last = StackGetInt(stack);
            int now = letterToInt(s[i]);

            if (last < now) {
                StackPut(stack, s[i], now-last);
            }
            else {
                StackPut(stack, intToLetter(last), last);
                StackPut(stack, s[i], now);
            }
        i++;
    }
    while (i--) {
        res += StackGetInt(stack);
    }

    StackFree(stack);
    return res;
}

int main() {
    printf("XXI: %d\n", romanToInt("MCMXCIV"));
    return 0;
}

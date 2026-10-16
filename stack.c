#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Initialize the stack
void CREATE(Stack *s) {
    s->top = -1;
}

// Check if the stack is full
int ISFULL(const Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Check if the stack is empty
int ISEMPTY(const Stack *s) {
    return s->top == -1;
}

// Add a point to the stack
int PUSH(Stack *s, Point elem) {
    if (ISFULL(s)) {
        return 0;
    }

    s->top++;
    s->elements[s->top] = elem;
    return 1;
}

// Remove and return the top point
Point POP(Stack *s) {
    if (ISEMPTY(s)) {
        fprintf(stderr, "Error: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    Point elem = s->elements[s->top];
    s->top--;
    return elem;
}

// Return the top point without removing it
Point TOP(const Stack *s) {
    if (ISEMPTY(s)) {
        fprintf(stderr, "Error: Stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return s->elements[s->top];
}

// Return the point below the top
Point NEXT_TO_TOP(const Stack *s) {
    if (s->top < 1) {
        fprintf(stderr, "Error: Not enough elements.\n");
        exit(EXIT_FAILURE);
    }

    return s->elements[s->top - 1];
}

#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 32768

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point elements[MAX_SIZE];
    int top;
} Stack;

// Stack operations
void CREATE(Stack *s);
int ISFULL(const Stack *s);
int ISEMPTY(const Stack *s);
int PUSH(Stack *s, Point elem);
Point POP(Stack *s);
Point TOP(const Stack *s);
Point NEXT_TO_TOP(const Stack *s);

#endif

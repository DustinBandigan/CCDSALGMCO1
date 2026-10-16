
#include <stdio.h>
#include "stack.h"

int main(void) {
    Stack s;
    CREATE(&s);

    Point p1 = {1.0, 2.0};
    Point p2 = {3.0, 4.0};
    Point p3 = {5.0, 6.0};

    PUSH(&s, p1);
    PUSH(&s, p2);
    PUSH(&s, p3);

    Point top = TOP(&s);
    printf("TOP: (%.2f, %.2f)\n", top.x, top.y);

    Point next = NEXT_TO_TOP(&s);
    printf("NEXT TO TOP: (%.2f, %.2f)\n", next.x, next.y);

    Point removed = POP(&s);
    printf("POPPED: (%.2f, %.2f)\n", removed.x, removed.y);

    printf("IS EMPTY: %d\n", ISEMPTY(&s));
    printf("IS FULL: %d\n", ISFULL(&s));

    return 0;
}

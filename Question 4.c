#include <stdio.h>
#define MAX 5   

void push(int stack[], int *top);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main() {
    int stack[MAX];
    int top = -1;   
    int choice;

    while (1) {
        printf("\n===== STACK MENU =====\n");
        printf("1. PUSH (Insert element)\n");
        printf("2. POP (Remove top element)\n");
        printf("3. PEEK (View top element)\n");
        printf("4. DISPLAY (Show all elements)\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push(stack, &top);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting program... Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}



void push(int stack[], int *top) {
    int value;
    if (*top == MAX - 1) {
        printf("\nStack Overflow! Cannot push more elements.\n");
    } else {
        printf("Enter value to push: ");
        scanf("%d", &value);
        *top = *top + 1;
        stack[*top] = value;
        printf("Pushed %d into the stack.\n", value);
    }
}

void pop(int stack[], int *top) {
    if (*top == -1) {
        printf("\nStack Underflow! No elements to pop.\n");
    } else {
        printf("Popped element: %d\n", stack[*top]);
        *top = *top - 1;
    }
}

void peek(int stack[], int top) {
    if (top == -1) {
        printf("\nStack is empty!\n");
    } else {
        printf("Top element is: %d\n", stack[top]);
    }
}

void display(int stack[], int top) {
    int i;
    if (top == -1) {
        printf("\nStack is empty!\n");
    } else {
        printf("\nStack elements (top to bottom):\n");
        for (i = top; i >= 0; i--) {
            printf("%d\n", stack[i]);
        }
    }
}


#include <stdio.h>
#include <stdlib.h>

struct KStack {
    int* arr;          // Array to store elements of all stacks
    int* top;          // Array to store the top index of each stack
    int* next;         // Array to store the next available index
    int stackCount;    // Number of stacks
    int capacity;      // Total capacity of the array
    int nextAvailable; // Next available index for pushing elements
};

// Function to create a k-stack with given capacity and number of stacks
struct KStack* createKStack(int k, int capacity) {
    struct KStack* kStack = (struct KStack*)malloc(sizeof(struct KStack));
    kStack->stackCount = k;
    kStack->capacity = capacity;
    kStack->nextAvailable = 0;

    // Allocate memory for arrays
    kStack->arr = (int*)malloc(sizeof(int) * capacity);
    kStack->top = (int*)malloc(sizeof(int) * k);
    kStack->next = (int*)malloc(sizeof(int) * capacity);

    // Initialize top and next for all stacks
    for (int i = 0; i < k; i++) {
        kStack->top[i] = -1;  // Initialize each stack as empty
        kStack->next[i] = i + 1;  // Set the next available index
    }
    kStack->next[k - 1] = -1;  // Mark the last segment as not having a next

    return kStack;
}

// Function to check if a stack is empty
int isEmpty(struct KStack* kStack, int stackNumber) {
    return (kStack->top[stackNumber] == -1);
}

// Function to check if a stack is full
int isFull(struct KStack* kStack) {
    return (kStack->nextAvailable == -1);
}

// Function to push an element onto a stack
void push(struct KStack* kStack, int stackNumber, int value) {
    if (isFull(kStack)) {
        printf("Stack Overflow\n");
        return;
    }

    int i = kStack->nextAvailable;  // Get the next available index
    kStack->nextAvailable = kStack->next[i];  // Update nextAvailable

    kStack->arr[i] = value;  // Store the value in the array
    kStack->next[i] = kStack->top[stackNumber];  // Update next for the stack
    kStack->top[stackNumber] = i;  // Update top for the stack
}

// Function to pop an element from a stack
int pop(struct KStack* kStack, int stackNumber) {
    if (isEmpty(kStack, stackNumber)) {
        printf("Stack %d is Empty\n", stackNumber);
        return -1;
    }

    int i = kStack->top[stackNumber];  // Get the current top index
    int value = kStack->arr[i];        // Get the value to be popped

    kStack->top[stackNumber] = kStack->next[i];  // Update top for the stack
    kStack->next[i] = kStack->nextAvailable;     // Update next for the element
    kStack->nextAvailable = i;                  // Update nextAvailable

    return value;
}

int main() {
    int k = 3;        // Number of stacks
    int capacity = 9; // Total capacity of the array
    struct KStack* kStack = createKStack(k, capacity);

    // Push elements into the stacks
    push(kStack, 0, 1);
    push(kStack, 1, 2);
    push(kStack, 2, 3);
    push(kStack, 0, 4);
    push(kStack, 1, 5);
    push(kStack, 2, 6);
    push(kStack, 0, 7);
    push(kStack, 1, 8);
    push(kStack, 2, 9);

    // Pop elements from the stacks and print
    printf("Popped from stack 0: %d\n", pop(kStack, 0));
    printf("Popped from stack 1: %d\n", pop(kStack, 1));
    printf("Popped from stack 2: %d\n", pop(kStack, 2));

    return 0;
}

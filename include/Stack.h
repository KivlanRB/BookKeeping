#ifndef STACK_H_
#define STACK_H_
#include <time.h>

/**
 * @brief A stack node. It has a string that represents the action comitted, 
 *  and a time_t var that represents the epoch time when the stack is commited.
 */
typedef struct stack{
    char history[150];
    time_t epoch_time;
    struct stack *next;
}Stack;

/**
 * @brief Push/Add a new element. It will automatically insert the current epoch time to the node.
 * 
 * @param head A stack that already has more than one element
 * @param history The element that we want to push to the stack
 */
void push_stack(Stack ** head, char *history);

/**
 * @brief Pop/Remove n-amount element, starting from the latest one
 * 
 * @param head The stack to pop
 * @param amount The amount of elements it goes through before it stops
 */
void pop_stack(Stack ** head, int amount);

/**
 * @brief Prints the stack in a user-friendly way
 * 
 * @param node The stack to print
 */
void print_stack(Stack * head);

/**
 * @brief Saves the stack to a file for later use.
 * 
 * @param head The stack to save.
 * @param filename The filename to save to.
 */
void save_stack(Stack * head, char *filename);

/**
 * @brief Initializes a stack with an element. It will automatically insert the current epoch time to the node.
 * 
 * @param history The element to save.
 * @return A stack pointer
 */
Stack *init_stack(char *history);

#endif
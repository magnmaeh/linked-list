#ifndef EXAMPLE_MY_STRUCT_H
#define EXAMPLE_MY_STRUCT_H

// Step 1. Include the linked_list_declarations.h file
#include "../inc/linked_list_declarations.h"

// Step 2. Define struct to generate linked list functions for
// Note: It must be typedefed
typedef struct my_struct
{
    int a;
    int b;
} my_struct_t;

// Step 3. Define a node using the macro below
LINKED_LIST_GENERIC_DEFINE_NODE(my_struct_t)

// Step 4. Define a meta (which acts as a read-only handle for your linked list)
LINKED_LIST_GENERIC_DEFINE_HANDLE(my_struct_t)

// Step 5. Declare all functions associated with the linked list
LINKED_LIST_GENERIC_DECLARE_ALL(my_struct_t)

#endif
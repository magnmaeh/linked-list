#ifndef EXAMPLE_DOUBLE_H
#define EXAMPLE_DOUBLE_H

// Step 1. Include the linked_list_declarations.h file
#include "../inc/linked_list_declarations.h"

// Step 2. Define struct to generate linked list functions for
// Note: For double this step is skipped

// Step 3. Define a node using the macro below
LINKED_LIST_GENERIC_DEFINE_NODE(double)

// Step 4. Define a meta (which acts as a read-only handle for your linked list)
LINKED_LIST_GENERIC_DEFINE_META(double)

// Step 5. Declare all functions associated with the linked list
LINKED_LIST_GENERIC_DECLARE_ALL(double)

#endif
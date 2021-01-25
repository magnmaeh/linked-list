# linked-list
Implements a generic linked list using the C preprocessor. The purpose of the project is to provide an extremely user light linked list: There are only really four macros the user needs to call in order to access an entire linked list module. 


### Functionality
The generic linked list provides 14 functions.
* initialize()
* insert_sorted()
* push()
* append()
* insert_after()
* traverse()
* peek()
* pop()
* get_at_pos()
* get_length()
* create_node_malloc()
* set_free_func()
* set_deepcopy_func()
* set_cmp_lt_func()

initialize() returns a handle to your linked list, which contains meta and configuration information about it - such as its length and which functions to call in order to free dynamically allocated memory. Even though the user can change the handle directly, it is advised to do so through the functions to avoid mistakes. 

The handle kind of looks like this (type = type of your choosing):
```c
struct handle
{
    struct node **ref;                                // Inaccessible to user
    void (*free)(void*);                              // Write only
    void (*deepcopy)(type, const type*);              // Write only
    unsigned char (*cmp_lt)(const type*, const type*) // Write only
    unsigned char length;                             // Read only
}
```

## How to use
Include the linked_list_declarations.h in a file you would like to keep the linked function declarations. Then simply:

```c
// Assuming a typedef my_struct_t exists above
LINKED_LIST_GENERIC_DEFINE_NODE(my_struct_t)
LINKED_LIST_GENERIC_DEFINE_HANDLE(my_struct_t)
LINKED_LIST_GENERIC_DECLARE_ALL(my_struct_t)
```

or perhaps

```c
LINKED_LIST_GENERIC_DEFINE_NODE(double)
LINKED_LIST_GENERIC_DEFINE_HANDLE(double)
LINKED_LIST_GENERIC_DECLARE_ALL(double)
```

Then open the .c file you want to define the functions. Then simply:

```c
LINKED_LIST_GENERIC_DEFINE_ALL(my_struct_t)
```

or perhaps

```c
LINKED_LIST_GENERIC_DEFINE_ALL(double)
```

This will give you access to all the functions mentioned above. To get only a selection of them, you may call the macros specific to those functions individually. Note that you must provide some functions to the module, such as a function to free your struct, one to deepcopy the contents of your struct to another, and optionally a function to compare your structed for use in the insert_sorted() function.

The reader is highly reccommended to view the steps shown in the 'examples' folder for more detailed description of use.

### Implementation details
The following shows an easy example of how a struct, function declaration, and function definition can be implemented using the C preprocessor.

```c
#define LINKED_LIST_GENERIC_DEFINE_NODE(type) \
struct node_##type \
{ \
    struct node_##type *next; \
    type *data; \
} \

#define LINKED_LIST_GENERIC_DECLARE_PEEK(type) \
type linked_list_##type##_peek(struct node_##type **ref); \

#define LINKED_LIST_GENERIC_DEFINE_PEEK(type) \
type linked_list_##type##_peek(struct node_##type **ref) \
{ \
    if (!ref) \
    { \
        return ...; \
    } \
 \
    else if (!*ref) \
    { \
        return ...; \
    } \
 \
    type *data = (*ref)->data; \
    return *data; \
} \

// In my_linked_list.h begin
typedef struct my_struct
{
    int a;
    int b;
} my_struct_t;

LINKED_LIST_GENERIC_DEFINE_NODE(my_struct_t)
LINKED_LIST_GENERIC_DECLARE_PEEK(my_struct_t)
// In my_linked_list.h end

// In my_linked_list.c begin
#include "my_linked_list.h"

LINKED_LIST_GENERIC_DEFINE_PEEK(my_struct_t)
// In my_linked_list.c end
```

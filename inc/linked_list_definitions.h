#ifndef LINKED_LIST_DEFINITIONS_H
#define LINKED_LIST_DEFINITIONS_H

#include <stdlib.h> // malloc(), free()

#include "linked_list_declarations.h"
#include "debug.h"
#include "errors.h"

#define LINKED_LIST_GENERIC_DEFINE_INITIALIZE(type) \
struct node_##type** linked_list_##type##_initialize() \
{ \
    struct node_##type **head = (struct node_##type **)linked_list_##type##_create_node_malloc(NULL, NULL); \
    _##type##_head[_list_index] = head; \
    return _##type##_head[_list_index]; \
} \

#define LINKED_LIST_GENERIC_DEFINE_INSERT_SORTED(type) \
unsigned char linked_list_##type##_insert_sorted(type* new_data, unsigned char (*cmp_lt_func)(const type*, const type *)) \
{ \
    if (new_data == NULL) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    if (_linked_list_length[_list_index] == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    /* No compare function provided */ \
    if (cmp_lt_func == NULL) \
    { \
        print_error("No compare function provided.\n"); \
        return -EINVAL; \
    } \
 \
    /* Linked list length is zero, so just add the data in any way */ \
    else if (_linked_list_length[_list_index] == 0) \
        return linked_list_##type##_push(new_data); \
 \
    /* Compare function says this node should be first in linked list */ \
    else if (!cmp_lt_func((*_##type##_head[_list_index])->data, new_data)) \
        return linked_list_##type##_push(new_data); \
 \
    else \
    { \
        unsigned char pos = 0; \
        struct node_##type *placeholder = *_##type##_head[_list_index]; \
        struct node_##type *current_node = *_##type##_head[_list_index]; \
 \
        while (current_node->next != NULL && current_node->next->data != NULL && \
               cmp_lt_func(current_node->next->data, new_data)) \
        { \
            current_node = current_node->next; \
            pos++; \
        } \
        *_##type##_head[_list_index] = placeholder; \
 \
        return linked_list_##type##_insert_after(new_data, pos); \
    } \
} \

#define LINKED_LIST_GENERIC_DEFINE_PUSH(type) \
unsigned char linked_list_##type##_push(type* new_data) \
{ \
    if (new_data == NULL) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    if (_linked_list_length[_list_index] == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    struct node_##type *new_node = linked_list_##type##_create_node_malloc(NULL, NULL); \
    new_node->data = new_data; \
    new_node->next = (*_##type##_head[_list_index]); \
    *_##type##_head[_list_index] = new_node; \
 \
    _linked_list_length[_list_index]++; \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_APPEND(type) \
unsigned char linked_list_##type##_append(type* new_data) \
{ \
    return linked_list_##type##_insert_after(new_data, _linked_list_length[_list_index] - 1); \
} \

#define LINKED_LIST_GENERIC_DEFINE_INSERT_AFTER(type) \
unsigned char linked_list_##type##_insert_after(type* new_data, const unsigned char pos) \
{ \
    if (new_data == NULL) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    /* Bit of a hack */ \
    if (_linked_list_length[_list_index] == 0) \
        linked_list_##type##_push(new_data); \
 \
    if (pos >= _linked_list_length[_list_index]) \
    { \
        print_error("pos > _linked_list_length[_list_index].\n"); \
        return -EINVAL; \
    } \
 \
    if (_linked_list_length[_list_index] == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    struct node_##type *placeholder = *_##type##_head[_list_index]; \
    struct node_##type *prev_node = *_##type##_head[_list_index]; \
 \
    for (unsigned char i = 0; i < pos; i++) \
        prev_node = prev_node->next; \
 \
    struct node_##type *new_node = linked_list_##type##_create_node_malloc(NULL, NULL); \
    new_node->data = new_data; \
    new_node->next = prev_node->next; \
    prev_node->next = new_node; \
 \
    *_##type##_head[_list_index] = placeholder; \
    _linked_list_length[_list_index]++; \
 \
    return 0; \
} \

#define LINKED_LIST_GENERIC_DEFINE_TRAVERSE(type) \
unsigned char linked_list_##type##_traverse(unsigned char (*func)(struct node_##type *)) \
{ \
    if (func == NULL) \
    { \
        print_error("func passed was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    if (_##type##_head[_list_index] == NULL || *_##type##_head[_list_index] == NULL) \
    { \
        print_error("linked list empty.\n"); \
        return -ENOLIS; \
    } \
 \
    struct node_##type* current_node = *_##type##_head[_list_index]; \
 \
    for (unsigned char i = 0; i < _linked_list_length[_list_index]; i++) \
    { \
        if (func(current_node)) \
        { \
            print_error("func passed returned an error.\n"); \
            return -EINVAL; \
        } \
 \
        if (i == _linked_list_length[_list_index] - 1) break; \
 \
        current_node = current_node->next; \
    } \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_PRINT(type) \
unsigned char linked_list_##type##_print(unsigned char (*printer)(struct node_##type *)) \
{ \
    if (printer == NULL) \
    { \
        print_error("printer passed was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    printf("Printing list %d\n", _list_index); \
    return linked_list_##type##_traverse(printer); \
} \

#define LINKED_LIST_GENERIC_DEFINE_PEEK(type) \
type linked_list_##type##_peek()  \
{ \
    if (_linked_list_length[_list_index] == 0) \
    { \
        print_error("_linked_list_length[_list_index] = 0\n"); \
        type ret; \
        return ret; \
    } \
 \
    return *(*_##type##_head[_list_index])->data; \
} \

#define LINKED_LIST_GENERIC_DEFINE_POP(type) \
type linked_list_##type##_pop() \
{ \
    if (_linked_list_length[_list_index] == 0) \
    { \
        print_error("_linked_list_length[_list_index] = 0.\n"); \
        type ret; \
        return ret; \
    } \
 \
    if (_##type##_head[_list_index] == NULL) \
    { \
        print_error("_head_ref == NULL.\n"); \
        type ret; \
        return ret; \
    } \
 \
    if (*_##type##_head[_list_index] == NULL) \
    { \
        print_error("_head_node == NULL.\n"); \
        type ret; \
        return ret; \
    } \
 \
    struct node_##type *temp = *_##type##_head[_list_index]; \
     \
    if (temp) \
    { \
         \
        *_##type##_head[_list_index] = temp->next; \
         \
    } \
 \
    _free_function[_list_index](temp); \
    _linked_list_length[_list_index]--; \
    return *temp->data; \
} \

#define LINKED_LIST_GENERIC_DEFINE_GET_AT_POS(type) \
type linked_list_##type##_get_at_pos(const unsigned char pos) \
{ \
    if (pos >= _linked_list_length[_list_index]) \
    { \
        print_error("pos >= _linked_list_length[_list_index].\n"); \
        type ret; \
        return ret; \
    } \
 \
    if (pos == 0) \
    { \
        return linked_list_##type##_pop(); \
    } \
 \
    struct node_##type *placeholder = *_##type##_head[_list_index]; \
    struct node_##type *current_node = *_##type##_head[_list_index]; \
    for (unsigned char i = 0; i < pos - 1; i++) \
    { \
        current_node = current_node->next; \
    } \
 \
    type ret = *current_node->next->data; \
    struct node_##type *temp = current_node->next; \
    current_node->next = current_node->next->next; \
    *_##type##_head[_list_index] = placeholder; \
 \
    _free_function[_list_index](temp); \
    _linked_list_length[_list_index]--; \
 \
    return ret; \
} \

#define LINKED_LIST_GENERIC_DEFINE_GET_LENGTH(type) \
unsigned char linked_list_##type##_get_length() \
{ \
    return _linked_list_length[_list_index]; \
} \

#define LINKED_LIST_GENERIC_DEFINE_CREATE_NODE_MALLOC(type) \
struct node_##type* linked_list_##type##_create_node_malloc(unsigned char (*setter_func)(struct node_##type*, type*), type* data) \
{ \
    struct node_##type* new_node = malloc(sizeof(struct node_##type)); \
 \
    if (new_node == NULL) \
    { \
        print_error("malloc() returned NULL.\n"); \
        return NULL; \
    } \
 \
    if (setter_func != NULL) \
    { \
        if (setter_func(new_node, data)) \
        { \
            print_error("setter_func() provided returned an error.\n"); \
            return NULL; \
        } \
    } \
 \
    return new_node; \
} \

#define LINKED_LIST_GENERIC_DEFINE_SET_FREE_FUNC(type) \
unsigned char linked_list_##type##_set_free_func(void (*free_func)(void*)) \
{ \
    if (free_func == NULL) \
    { \
        print_error("free_func() was NULL.\n"); \
        return -EINVAL; \
    } \
    _free_function[_list_index] = free_func; \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_SET_LIST_INDEX(type) \
unsigned char linked_list_##type##_set_list_index(const unsigned char new_index) \
{ \
    if (new_index < 0 || LINKED_LIST_MAX_LISTS < new_index) \
    { \
        print_error("new_index out of range.\n"); \
        return -EINVAL; \
    } \
 \
    _list_index = new_index; \
 \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_ALL(type) \
LINKED_LIST_GENERIC_DEFINE_INITIALIZE(type) \
LINKED_LIST_GENERIC_DEFINE_INSERT_SORTED(type) \
LINKED_LIST_GENERIC_DEFINE_PUSH(type) \
LINKED_LIST_GENERIC_DEFINE_APPEND(type) \
LINKED_LIST_GENERIC_DEFINE_INSERT_AFTER(type) \
LINKED_LIST_GENERIC_DEFINE_TRAVERSE(type) \
LINKED_LIST_GENERIC_DEFINE_PRINT(type) \
LINKED_LIST_GENERIC_DEFINE_PEEK(type) \
LINKED_LIST_GENERIC_DEFINE_POP(type) \
LINKED_LIST_GENERIC_DEFINE_GET_AT_POS(type) \
LINKED_LIST_GENERIC_DEFINE_GET_LENGTH(type) \
LINKED_LIST_GENERIC_DEFINE_CREATE_NODE_MALLOC(type) \
LINKED_LIST_GENERIC_DEFINE_SET_FREE_FUNC(type) \
LINKED_LIST_GENERIC_DEFINE_SET_LIST_INDEX(type) \

#endif // LINKED_LIST_DEFINITIONS_H
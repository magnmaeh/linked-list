#ifndef LINKED_LIST_DEFINITIONS_H
#define LINKED_LIST_DEFINITIONS_H

#include <stdlib.h> // malloc(), free()

#include "linked_list_declarations.h"
#include "debug.h"
#include "errors.h"

#define LINKED_LIST_GENERIC_DEFINE_INITIALIZE(type) \
struct handle_##type linked_list_##type##_initialize() \
{ \
    struct node_##type **ref = (struct node_##type **) linked_list_##type##_create_node_malloc(NULL); \
    struct handle_##type handle = { .ref = ref, .length = 0 }; \
    return handle; \
} \

#define LINKED_LIST_GENERIC_DEFINE_INSERT_SORTED(type) \
unsigned char linked_list_##type##_insert_sorted(struct handle_##type *handle, type* new_data) \
{ \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!new_data) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (handle->length == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    /* No compare function provided */ \
    else if (!handle->cmp_lt) \
    { \
        print_error("handle has no cmp lt function.\n"); \
        return -EINVAL; \
    } \
 \
    /* Linked list length is zero, so just add the data in any way */ \
    else if (handle->length == 0) \
        return linked_list_##type##_push(handle, new_data); \
 \
    struct node_##type **ref = handle->ref; \
 \
    /* Compare function says this node should be first in linked list */ \
    if (!handle->cmp_lt((*ref)->data, new_data)) \
        return linked_list_##type##_push(handle, new_data); \
 \
    else \
    { \
        unsigned char pos = 0; \
        struct node_##type *placeholder = *ref; \
        struct node_##type *current_node = *ref; \
 \
        while (current_node->next != NULL && current_node->next->data != NULL && \
               handle->cmp_lt(current_node->next->data, new_data)) \
        { \
            current_node = current_node->next; \
            if (pos == handle->length - 1) break; \
            pos++; \
        } \
        *ref = placeholder; \
 \
        return linked_list_##type##_insert_after(handle, new_data, pos); \
    } \
} \

#define LINKED_LIST_GENERIC_DEFINE_PUSH(type) \
unsigned char linked_list_##type##_push(struct handle_##type *handle, type *new_data) \
{ \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!new_data) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (handle->length == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    struct node_##type **ref = handle->ref; \
    struct node_##type *new_node = linked_list_##type##_create_node_malloc(new_data); \
 \
    new_node->next = *ref; \
    *ref = new_node; \
    handle->length++; \
 \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_APPEND(type) \
unsigned char linked_list_##type##_append(struct handle_##type *handle, type *new_data) \
{ \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!new_data) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (handle->length == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    else if (handle->length == 0) \
        return linked_list_##type##_push(handle, new_data); \
 \
    return linked_list_##type##_insert_after(handle, new_data, handle->length - 1); \
} \

#define LINKED_LIST_GENERIC_DEFINE_INSERT_AFTER(type) \
unsigned char linked_list_##type##_insert_after(struct handle_##type *handle, type *new_data, const unsigned char pos) \
{ \
    if (!handle) \
    { \
        printf("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (new_data == NULL) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    /* Bit of a hack */ \
    else if (handle->length == 0) \
        linked_list_##type##_push(handle, new_data); \
 \
    else if (pos >= handle->length) \
    { \
        print_error("pos > handle->length.\n"); \
        return -EINVAL; \
    } \
 \
    else if (handle->length == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    struct node_##type **ref = handle->ref;\
 \
    struct node_##type *placeholder = *ref; \
    struct node_##type *prev_node = *ref; \
 \
    for (unsigned char i = 0; i < pos; i++) \
        prev_node = prev_node->next; \
 \
    struct node_##type *new_node = linked_list_##type##_create_node_malloc(new_data); \
    new_node->next = prev_node->next; \
    prev_node->next = new_node; \
 \
    *ref = placeholder; \
    handle->length++; \
 \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_TRAVERSE(type) \
unsigned char linked_list_##type##_traverse(struct handle_##type *handle, unsigned char (*func)(struct node_##type *)) \
{ \
    if (!func) \
    { \
        print_error("func passed was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    struct node_##type **ref = handle->ref; \
 \
    if (handle->length == 0) \
    { \
        print_error("linked list empty.\n"); \
        return -ENOLIS; \
    } \
 \
    struct node_##type* current_node = *ref; \
 \
    for (unsigned char i = 0; i < handle->length; i++) \
    { \
        if (func(current_node)) \
        { \
            print_error("func passed returned an error.\n"); \
            return -EINVAL; \
        } \
 \
        if (i == handle->length - 1) break; \
 \
        current_node = current_node->next; \
    } \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_PEEK(type) \
type linked_list_##type##_peek(struct handle_##type *handle)  \
{ \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        type ret; \
        return ret; \
    } \
 \
    else if (handle->length == 0) \
    { \
        print_error("_linked_list_length[_list_index] = 0\n"); \
        type ret; \
        return ret; \
    } \
 \
    struct node_##type **ref = handle->ref; \
    type *data = (*ref)->data; \
 \
    return *data; \
} \

#define LINKED_LIST_GENERIC_DEFINE_POP(type) \
type linked_list_##type##_pop(struct handle_##type *handle) \
{ \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        type ret; \
        return ret; \
    } \
 \
    else if (handle->length == 0) \
    { \
        print_error("handle->length = 0.\n"); \
        type ret; \
        return ret; \
    } \
 \
    struct node_##type **ref = handle->ref; \
 \
    if (handle->length == 0) \
    { \
        print_error("Linked list empty.\n"); \
        type ret; \
        return ret; \
    } \
 \
    struct node_##type *temp = *ref; \
     \
    if (temp) \
        *ref = temp->next; \
 \
    type ret; \
    handle->deepcopy(&ret, temp->data); \
    handle->free_function(temp); \
    handle->length--; \
 \
    return ret; \
} \

#define LINKED_LIST_GENERIC_DEFINE_GET_AT_POS(type) \
type linked_list_##type##_get_at_pos(struct handle_##type *handle, const unsigned char pos) \
{ \
    if (pos >= handle->length) \
    { \
        print_error("pos >= handle->length\n"); \
        type ret; \
        return ret; \
    } \
 \
    else if (pos == 0) \
        return linked_list_##type##_pop(handle); \
 \
    struct node_##type **ref = handle->ref; \
 \
    struct node_##type *placeholder = *ref; \
    struct node_##type *current_node = *ref; \
 \
    for (unsigned char i = 0; i < pos - 1; i++) \
        current_node = current_node->next; \
 \
    struct node_##type *temp = current_node->next; \
    current_node->next = current_node->next->next; \
    *ref = placeholder; \
 \
    type ret; \
    handle->deepcopy(&ret, temp->data); \
    handle->free_function(temp); \
    handle->length--; \
 \
    return ret; \
} \

#define LINKED_LIST_GENERIC_DEFINE_GET_LENGTH(type) \
unsigned char linked_list_##type##_get_length(struct handle_##type *handle) \
{  \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    return handle->length; \
} \

#define LINKED_LIST_GENERIC_DEFINE_CREATE_NODE_MALLOC(type) \
struct node_##type* linked_list_##type##_create_node_malloc(type* data) \
{ \
    struct node_##type* new_node = malloc(sizeof(struct node_##type)); \
 \
    if (new_node == NULL) \
    { \
        print_error("malloc() returned NULL.\n"); \
        return NULL; \
    } \
    new_node->data = data; \
 \
    return new_node; \
} \

#define LINKED_LIST_GENERIC_DEFINE_SET_FREE_FUNC(type) \
unsigned char linked_list_##type##_set_free_func(struct handle_##type *handle, void (*free_func)(void*)) \
{ \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!free_func) \
    { \
        print_error("free_func() was NULL.\n"); \
        return -EINVAL; \
    } \
    handle->free_function = free_func; \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_SET_DEEPCOPY_FUNC(type) \
unsigned char linked_list_##type##_set_deepcopy_func(struct handle_##type *handle, void (*deepcopy_func)(type*, const type*)) \
{ \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!deepcopy_func) \
    { \
        print_error("deepcopy func was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    handle->deepcopy = deepcopy_func; \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_SET_CMP_LT_FUNC(type) \
unsigned char linked_list_##type##_set_cmp_lt_func(struct handle_##type *handle, unsigned char (*cmp_lt_func)(const type*, const type*)) \
{ \
    if (!handle) \
    { \
        print_error("handle was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!cmp_lt_func) \
    { \
        print_error("cmp lt func was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    handle->cmp_lt = cmp_lt_func; \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_ALL(type) \
LINKED_LIST_GENERIC_DEFINE_INITIALIZE(type) \
LINKED_LIST_GENERIC_DEFINE_INSERT_SORTED(type) \
LINKED_LIST_GENERIC_DEFINE_PUSH(type) \
LINKED_LIST_GENERIC_DEFINE_APPEND(type) \
LINKED_LIST_GENERIC_DEFINE_INSERT_AFTER(type) \
LINKED_LIST_GENERIC_DEFINE_TRAVERSE(type) \
LINKED_LIST_GENERIC_DEFINE_PEEK(type) \
LINKED_LIST_GENERIC_DEFINE_POP(type) \
LINKED_LIST_GENERIC_DEFINE_GET_AT_POS(type) \
LINKED_LIST_GENERIC_DEFINE_GET_LENGTH(type) \
LINKED_LIST_GENERIC_DEFINE_CREATE_NODE_MALLOC(type) \
LINKED_LIST_GENERIC_DEFINE_SET_FREE_FUNC(type) \
LINKED_LIST_GENERIC_DEFINE_SET_DEEPCOPY_FUNC(type) \
LINKED_LIST_GENERIC_DEFINE_SET_CMP_LT_FUNC(type) \

#endif // LINKED_LIST_DEFINITIONS_H
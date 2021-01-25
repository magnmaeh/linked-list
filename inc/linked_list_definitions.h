#ifndef LINKED_LIST_DEFINITIONS_H
#define LINKED_LIST_DEFINITIONS_H

#include <stdlib.h> // malloc(), free()

#include "linked_list_declarations.h"
#include "debug.h"
#include "errors.h"

#define LINKED_LIST_GENERIC_DEFINE_INITIALIZE(type) \
struct meta_##type linked_list_##type##_initialize() \
{ \
    struct node_##type **ref = (struct node_##type **) linked_list_##type##_create_node_malloc(NULL); \
    struct meta_##type meta = { .ref = ref, .length = 0 }; \
    return meta; \
} \

#define LINKED_LIST_GENERIC_DEFINE_INSERT_SORTED(type) \
unsigned char linked_list_##type##_insert_sorted(struct meta_##type *meta, type* new_data) \
{ \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!new_data) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (meta->length == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    /* No compare function provided */ \
    else if (!meta->cmp_lt) \
    { \
        print_error("meta has no cmp lt function.\n"); \
        return -EINVAL; \
    } \
 \
    /* Linked list length is zero, so just add the data in any way */ \
    else if (meta->length == 0) \
        return linked_list_##type##_push(meta, new_data); \
 \
    struct node_##type **ref = meta->ref; \
 \
    /* Compare function says this node should be first in linked list */ \
    if (!meta->cmp_lt((*ref)->data, new_data)) \
        return linked_list_##type##_push(meta, new_data); \
 \
    else \
    { \
        unsigned char pos = 0; \
        struct node_##type *placeholder = *ref; \
        struct node_##type *current_node = *ref; \
 \
        while (current_node->next != NULL && current_node->next->data != NULL && \
               meta->cmp_lt(current_node->next->data, new_data)) \
        { \
            current_node = current_node->next; \
            if (pos == meta->length - 1) break; \
            pos++; \
        } \
        *ref = placeholder; \
 \
        return linked_list_##type##_insert_after(meta, new_data, pos); \
    } \
} \

#define LINKED_LIST_GENERIC_DEFINE_PUSH(type) \
unsigned char linked_list_##type##_push(struct meta_##type *meta, type *new_data) \
{ \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!new_data) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (meta->length == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    struct node_##type **ref = meta->ref; \
    struct node_##type *new_node = linked_list_##type##_create_node_malloc(new_data); \
 \
    new_node->next = *ref; \
    *ref = new_node; \
    meta->length++; \
 \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_APPEND(type) \
unsigned char linked_list_##type##_append(struct meta_##type *meta, type *new_data) \
{ \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!new_data) \
    { \
        print_error("new_data was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (meta->length == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    else if (meta->length == 0) \
        return linked_list_##type##_push(meta, new_data); \
 \
    return linked_list_##type##_insert_after(meta, new_data, meta->length - 1); \
} \

#define LINKED_LIST_GENERIC_DEFINE_INSERT_AFTER(type) \
unsigned char linked_list_##type##_insert_after(struct meta_##type *meta, type *new_data, const unsigned char pos) \
{ \
    if (!meta) \
    { \
        printf("meta was NULL.\n"); \
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
    else if (meta->length == 0) \
        linked_list_##type##_push(meta, new_data); \
 \
    else if (pos >= meta->length) \
    { \
        print_error("pos > meta->length.\n"); \
        return -EINVAL; \
    } \
 \
    else if (meta->length == LINKED_LIST_MAX_LENGTH) \
    { \
        print_error("Linked list full.\n"); \
        return -ENOBUF; \
    } \
 \
    struct node_##type **ref = meta->ref;\
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
    meta->length++; \
 \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_TRAVERSE(type) \
unsigned char linked_list_##type##_traverse(struct meta_##type *meta, unsigned char (*func)(struct node_##type *)) \
{ \
    if (!func) \
    { \
        print_error("func passed was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    struct node_##type **ref = meta->ref; \
 \
    if (meta->length == 0) \
    { \
        print_error("linked list empty.\n"); \
        return -ENOLIS; \
    } \
 \
    struct node_##type* current_node = *ref; \
 \
    for (unsigned char i = 0; i < meta->length; i++) \
    { \
        printf("Call func on node %d with data %f\n", current_node, *current_node->data); \
        if (func(current_node)) \
        { \
            print_error("func passed returned an error.\n"); \
            return -EINVAL; \
        } \
 \
        if (i == meta->length - 1) break; \
 \
        current_node = current_node->next; \
    } \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_PEEK(type) \
type linked_list_##type##_peek(struct meta_##type *meta)  \
{ \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        type ret; \
        return ret; \
    } \
 \
    else if (meta->length == 0) \
    { \
        print_error("_linked_list_length[_list_index] = 0\n"); \
        type ret; \
        return ret; \
    } \
 \
    struct node_##type **ref = meta->ref; \
    type *data = (*ref)->data; \
 \
    return *data; \
} \

#define LINKED_LIST_GENERIC_DEFINE_POP(type) \
type linked_list_##type##_pop(struct meta_##type *meta) \
{ \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        type ret; \
        return ret; \
    } \
 \
    else if (meta->length == 0) \
    { \
        print_error("meta->length = 0.\n"); \
        type ret; \
        return ret; \
    } \
 \
    struct node_##type **ref = meta->ref; \
 \
    if (meta->length == 0) \
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
    meta->deepcopy(&ret, temp->data); \
    meta->free_function(temp); \
    meta->length--; \
 \
    return ret; \
} \

#define LINKED_LIST_GENERIC_DEFINE_GET_AT_POS(type) \
type linked_list_##type##_get_at_pos(struct meta_##type *meta, const unsigned char pos) \
{ \
    if (pos >= meta->length) \
    { \
        print_error("pos >= meta->length\n"); \
        type ret; \
        return ret; \
    } \
 \
    else if (pos == 0) \
        return linked_list_##type##_pop(meta); \
 \
    struct node_##type **ref = meta->ref; \
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
    meta->deepcopy(&ret, temp->data); \
    meta->free_function(temp); \
    meta->length--; \
 \
    return ret; \
} \

#define LINKED_LIST_GENERIC_DEFINE_GET_LENGTH(type) \
unsigned char linked_list_##type##_get_length(struct meta_##type *meta) \
{  \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    return meta->length; \
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
unsigned char linked_list_##type##_set_free_func(struct meta_##type *meta, void (*free_func)(void*)) \
{ \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!free_func) \
    { \
        print_error("free_func() was NULL.\n"); \
        return -EINVAL; \
    } \
    meta->free_function = free_func; \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_SET_DEEPCOPY_FUNC(type) \
unsigned char linked_list_##type##_set_deepcopy_func(struct meta_##type *meta, void (*deepcopy_func)(type*, const type*)) \
{ \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!deepcopy_func) \
    { \
        print_error("deepcopy func was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    meta->deepcopy = deepcopy_func; \
    return ENOERR; \
} \

#define LINKED_LIST_GENERIC_DEFINE_SET_CMP_LT_FUNC(type) \
unsigned char linked_list_##type##_set_cmp_lt_func(struct meta_##type *meta, unsigned char (*cmp_lt_func)(const type*, const type*)) \
{ \
    if (!meta) \
    { \
        print_error("meta was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    else if (!cmp_lt_func) \
    { \
        print_error("cmp lt func was NULL.\n"); \
        return -EINVAL; \
    } \
 \
    meta->cmp_lt = cmp_lt_func; \
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
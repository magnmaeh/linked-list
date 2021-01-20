#ifndef LINKED_LIST_DECLARATIONS_H
#define LINKED_LIST_DECLARATIONS_H

#define LINKED_LIST_MAX_LENGTH  20
#define LINKED_LIST_MAX_LISTS   3

typedef struct {
    int a;
    int b;
} my_struct;

#define LINKED_LIST_GENERIC_DEFINE_NODE(type) \
struct node_##type \
{ \
    struct node_##type *next; \
    type *data; \
}; \

#define LINKED_LIST_GENERIC_DECLARE_LOCAL_HEAD(type) \
struct node_##type **_##type##_head = NULL; \

#define LINKED_LIST_GENERIC_DECLARE_INITIALIZE(type) \
struct node_##type** linked_list_##type##_initialize(); \

#define LINKED_LIST_GENERIC_DECLARE_INSERT_SORTED(type) \
unsigned char linked_list_##type##_insert_sorted(type* new_data, unsigned char (*cmp_lt_func)(const type *, const type *)); \

#define LINKED_LIST_GENERIC_DECLARE_PUSH(type) \
unsigned char linked_list_##type##_push(type* new_data); \

#define LINKED_LIST_GENERIC_DECLARE_APPEND(type) \
unsigned char linked_list_##type##_append(type* new_data);

#define LINKED_LIST_GENERIC_DECLARE_INSERT_AFTER(type) \
unsigned char linked_list_##type##_insert_after(type* new_data, const unsigned char pos); \

#define LINKED_LIST_GENERIC_DECLARE_TRAVERSE(type) \
unsigned char linked_list_##type##_traverse(unsigned char (*func)(struct node_##type *));

#define LINKED_LIST_GENERIC_DECLARE_PRINT(type) \
unsigned char linked_list_##type##_print(unsigned char (*printer)(struct node_##type *));

#define LINKED_LIST_GENERIC_DECLARE_PEEK(type) \
type linked_list_##type##_peek(); \

#define LINKED_LIST_GENERIC_DECLARE_POP(type) \
type linked_list_##type##_pop(); \

#define LINKED_LIST_GENERIC_DECLARE_GET_AT_POS(type) \
type linked_list_##type##_get_at_pos(const unsigned char pos); \

#define LINKED_LIST_GENERIC_DECLARE_GET_LENGTH(type) \
unsigned char linked_list_##type##_get_length(); \

#define LINKED_LIST_GENERIC_DECLARE_CREATE_NODE_MALLOC(type) \
struct node_##type* linked_list_##type##_create_node_malloc(unsigned char (*setter_func)(struct node_##type*, type*), type* data); \

#define LINKED_LIST_GENERIC_DECLARE_SET_FREE_FUNC(type) \
unsigned char linked_list_##type##_set_free_func(void (*free_func)(void*)); \

#define LINKED_LIST_GENERIC_DECLARE_SET_LIST_INDEX(type) \
unsigned char linked_list_##type##_set_list_index(const unsigned char new_index);


#define LINKED_LIST_GENERIC_DECLARE_ALL(type) \
LINKED_LIST_GENERIC_DECLARE_INITIALIZE(type) \
LINKED_LIST_GENERIC_DECLARE_INSERT_SORTED(type) \
LINKED_LIST_GENERIC_DECLARE_PUSH(type) \
LINKED_LIST_GENERIC_DECLARE_APPEND(type) \
LINKED_LIST_GENERIC_DECLARE_INSERT_AFTER(type) \
LINKED_LIST_GENERIC_DECLARE_TRAVERSE(type) \
LINKED_LIST_GENERIC_DECLARE_PRINT(type) \
LINKED_LIST_GENERIC_DECLARE_PEEK(type) \
LINKED_LIST_GENERIC_DECLARE_POP(type) \
LINKED_LIST_GENERIC_DECLARE_GET_AT_POS(type) \
LINKED_LIST_GENERIC_DECLARE_GET_LENGTH(type) \
LINKED_LIST_GENERIC_DECLARE_CREATE_NODE_MALLOC(type) \
LINKED_LIST_GENERIC_DECLARE_SET_FREE_FUNC(type) \
LINKED_LIST_GENERIC_DECLARE_SET_LIST_INDEX(type) \

LINKED_LIST_GENERIC_DEFINE_NODE(my_struct)
LINKED_LIST_GENERIC_DECLARE_ALL(my_struct)

#endif // LINKED_LIST_DECLARATIONS_H
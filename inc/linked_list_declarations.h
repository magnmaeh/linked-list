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

#define LINKED_LIST_GENERIC_DEFINE_META(type) \
struct meta_##type \
{ \
    struct node_##type **ref; \
    void (*free_function)(void*); \
    void (*deepcopy)(type*, const type*); \
    unsigned char (*cmp_lt)(const type*, const type*); \
    unsigned char length; \
}; \


#define LINKED_LIST_GENERIC_DECLARE_INITIALIZE(type) \
struct meta_##type linked_list_##type##_initialize(); \

#define LINKED_LIST_GENERIC_DECLARE_INSERT_SORTED(type) \
unsigned char linked_list_##type##_insert_sorted(struct meta_##type *meta, type* new_data); \

#define LINKED_LIST_GENERIC_DECLARE_PUSH(type) \
unsigned char linked_list_##type##_push(struct meta_##type *meta, type* new_data); \

#define LINKED_LIST_GENERIC_DECLARE_APPEND(type) \
unsigned char linked_list_##type##_append(struct meta_##type *meta, type* new_data);

#define LINKED_LIST_GENERIC_DECLARE_INSERT_AFTER(type) \
unsigned char linked_list_##type##_insert_after(struct meta_##type *meta, type* new_data, const unsigned char pos); \

#define LINKED_LIST_GENERIC_DECLARE_TRAVERSE(type) \
unsigned char linked_list_##type##_traverse(struct meta_##type *meta, unsigned char (*func)(struct node_##type *));

#define LINKED_LIST_GENERIC_DECLARE_PEEK(type) \
type linked_list_##type##_peek(struct meta_##type *meta); \

#define LINKED_LIST_GENERIC_DECLARE_POP(type) \
type linked_list_##type##_pop(struct meta_##type *meta); \

#define LINKED_LIST_GENERIC_DECLARE_GET_AT_POS(type) \
type linked_list_##type##_get_at_pos(struct meta_##type *meta, const unsigned char pos); \

#define LINKED_LIST_GENERIC_DECLARE_GET_LENGTH(type) \
unsigned char linked_list_##type##_get_length(struct meta_##type *meta); \

#define LINKED_LIST_GENERIC_DECLARE_CREATE_NODE_MALLOC(type) \
struct node_##type* linked_list_##type##_create_node_malloc(type* data); \

#define LINKED_LIST_GENERIC_DECLARE_SET_FREE_FUNC(type) \
unsigned char linked_list_##type##_set_free_func(struct meta_##type *meta, void (*free_func)(void*)); \

#define LINKED_LIST_GENERIC_DECLARE_SET_DEEPCOPY_FUNC(type) \
unsigned char linked_list_##type##_set_deepcopy_func(struct meta_##type *meta, void (*deepcopy_func)(type*, const type*)); \

#define LINKED_LIST_GENERIC_DECLARE_SET_CMP_LT_FUNC(type) \
unsigned char linked_list_##type##_set_cmp_lt_func(struct meta_##type *meta, unsigned char (*cmp_lt_func)(const type*, const type*)); \

#define LINKED_LIST_GENERIC_DECLARE_ALL(type) \
LINKED_LIST_GENERIC_DECLARE_INITIALIZE(type) \
LINKED_LIST_GENERIC_DECLARE_INSERT_SORTED(type) \
LINKED_LIST_GENERIC_DECLARE_PUSH(type) \
LINKED_LIST_GENERIC_DECLARE_APPEND(type) \
LINKED_LIST_GENERIC_DECLARE_INSERT_AFTER(type) \
LINKED_LIST_GENERIC_DECLARE_TRAVERSE(type) \
LINKED_LIST_GENERIC_DECLARE_PEEK(type) \
LINKED_LIST_GENERIC_DECLARE_POP(type) \
LINKED_LIST_GENERIC_DECLARE_GET_AT_POS(type) \
LINKED_LIST_GENERIC_DECLARE_GET_LENGTH(type) \
LINKED_LIST_GENERIC_DECLARE_CREATE_NODE_MALLOC(type) \
LINKED_LIST_GENERIC_DECLARE_SET_FREE_FUNC(type) \
LINKED_LIST_GENERIC_DECLARE_SET_DEEPCOPY_FUNC(type) \
LINKED_LIST_GENERIC_DECLARE_SET_CMP_LT_FUNC(type) \


#endif // LINKED_LIST_DECLARATIONS_H
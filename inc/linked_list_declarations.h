/*
 * Copyright (C) 2020 Magnus Mæhlum
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

#define LINKED_LIST_GENERIC_DEFINE_HANDLE(type) \
struct handle_##type \
{ \
    struct node_##type **ref; \
    void (*free_function)(void*); \
    void (*deepcopy)(type*, const type*); \
    unsigned char (*cmp_lt)(const type*, const type*); \
    unsigned char length; \
}; \


#define LINKED_LIST_GENERIC_DECLARE_INITIALIZE(type) \
struct handle_##type linked_list_##type##_initialize(); \

#define LINKED_LIST_GENERIC_DECLARE_INSERT_SORTED(type) \
unsigned char linked_list_##type##_insert_sorted(struct handle_##type *handle, type* new_data); \

#define LINKED_LIST_GENERIC_DECLARE_PUSH(type) \
unsigned char linked_list_##type##_push(struct handle_##type *handle, type* new_data); \

#define LINKED_LIST_GENERIC_DECLARE_APPEND(type) \
unsigned char linked_list_##type##_append(struct handle_##type *handle, type* new_data);

#define LINKED_LIST_GENERIC_DECLARE_INSERT_AFTER(type) \
unsigned char linked_list_##type##_insert_after(struct handle_##type *handle, type* new_data, const unsigned char pos); \

#define LINKED_LIST_GENERIC_DECLARE_TRAVERSE(type) \
unsigned char linked_list_##type##_traverse(struct handle_##type *handle, unsigned char (*func)(struct node_##type *));

#define LINKED_LIST_GENERIC_DECLARE_PEEK(type) \
type linked_list_##type##_peek(struct handle_##type *handle); \

#define LINKED_LIST_GENERIC_DECLARE_POP(type) \
type linked_list_##type##_pop(struct handle_##type *handle); \

#define LINKED_LIST_GENERIC_DECLARE_GET_AT_POS(type) \
type linked_list_##type##_get_at_pos(struct handle_##type *handle, const unsigned char pos); \

#define LINKED_LIST_GENERIC_DECLARE_GET_LENGTH(type) \
unsigned char linked_list_##type##_get_length(struct handle_##type *handle); \

#define LINKED_LIST_GENERIC_DECLARE_CREATE_NODE_MALLOC(type) \
struct node_##type* linked_list_##type##_create_node_malloc(type* data); \

#define LINKED_LIST_GENERIC_DECLARE_SET_FREE_FUNC(type) \
unsigned char linked_list_##type##_set_free_func(struct handle_##type *handle, void (*free_func)(void*)); \

#define LINKED_LIST_GENERIC_DECLARE_SET_DEEPCOPY_FUNC(type) \
unsigned char linked_list_##type##_set_deepcopy_func(struct handle_##type *handle, void (*deepcopy_func)(type*, const type*)); \

#define LINKED_LIST_GENERIC_DECLARE_SET_CMP_LT_FUNC(type) \
unsigned char linked_list_##type##_set_cmp_lt_func(struct handle_##type *handle, unsigned char (*cmp_lt_func)(const type*, const type*)); \

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
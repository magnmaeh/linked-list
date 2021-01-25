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

// Step 1. Include linked_list_definitions.h file along with your own .h file
#include "linked_list_definitions.h"
#include "example_my_struct.h"

// Step 2. Define all the functions declared in the .h file
LINKED_LIST_GENERIC_DEFINE_ALL(my_struct_t)

// Step 3. Implement these functions for your struct (if your struct needs them)
// Note: In some cases these functions simply reduce to the normal 'free()'
static void _my_struct_free(void *strct);
static void _my_struct_deepcopy(my_struct_t *lhs, const my_struct_t *rhs);

// Step 3.1 If you want to use 'linked_list_ _insert_sorted()', you must also
// implement a function that returns 1 if struct 1 < struct 2 (strict inequality).
static unsigned char _my_struct_cmp_lt(const my_struct_t *lhs, const my_struct_t *rhs);

// For tests: linked_list_ _traverse()
static unsigned char _print_node(struct node_my_struct_t *node)
{
    printf("------------------\n");
    printf("node->data->a = %d\n", node->data->a);
    printf("node->data->b = %d\n", node->data->b);
    printf("------------------\n");
    return 0;
}

// For tests: linked_list_ _traverse()
static unsigned char _increment(struct node_my_struct_t *node)
{
    node->data->a++;
    node->data->b++;
    return 0;
}

// For tests: linked_list_ _insert_sorted()
static unsigned char _cmp_eq(const my_struct_t *lhs, const my_struct_t *rhs)
{
    if (lhs->a != rhs->a || lhs->b != rhs->b) return 0;
    return 1;
}


int my_struct_test()
{
    /*** Initialization sequence begin ***/
   
    // Step 1. Initialize and save the handle the function returns
    struct handle_my_struct_t handle = linked_list_my_struct_t_initialize();
    struct handle_my_struct_t *h = &handle;

    // Step 2. Set the handle's 'free()' and 'deepcopy()' with designated functions
    linked_list_my_struct_t_set_free_func(h, _my_struct_free);
    linked_list_my_struct_t_set_deepcopy_func(h, _my_struct_deepcopy);

    // Step 2.1 Set the handle's 'cmp_lt' with designated function
    linked_list_my_struct_t_set_cmp_lt_func(h, _my_struct_cmp_lt);

    /*** Initialization sequence end ***/

   
    // Tips and tricks
    /* 1. As a debugger, it would be a good idea to implement a function that 
          prints each node and pass it to 'linked_list_ _traverse()', which
          will execute that function on each node in your linked list.
       2. There is no limit on how many linked lists you initialize.
    */

    // Tests below
    my_struct_t data = { .a = 12, .b = 12 };
    my_struct_t data2 = { .a = 17, .b = 13 };
    my_struct_t data3 = { .a = 11, .b = 12 };
    my_struct_t data4 = { .a = 6, .b = 2 };
   
    linked_list_my_struct_t_insert_sorted(h, &data);
    linked_list_my_struct_t_insert_sorted(h, &data2);
    linked_list_my_struct_t_insert_sorted(h, &data3);
    linked_list_my_struct_t_insert_sorted(h, &data4);

    if (linked_list_my_struct_t_get_length(h) != 4)
        printf("Error in length!\n");

    linked_list_my_struct_t_traverse(h, _print_node);

    my_struct_t out_data = linked_list_my_struct_t_pop(h);
    my_struct_t out_data2 = linked_list_my_struct_t_pop(h);
    my_struct_t out_data3 = linked_list_my_struct_t_pop(h);
    my_struct_t out_data4 = linked_list_my_struct_t_pop(h);

    if (linked_list_my_struct_t_get_length(h) != 0)
        printf("Error in length!\n");

    linked_list_my_struct_t_traverse(h, _print_node);

    if (!_cmp_eq(&out_data, &data4))
    {
        printf("Error in sorting sequence!\n");
    }
    if (!_cmp_eq(&out_data2, &data3))
    {
        printf("Error in sorting sequence!\n");
    }
    if (!_cmp_eq(&out_data3, &data))
    {
        printf("Error in sorting sequence!\n");
    }
    if (!_cmp_eq(&out_data4, &data2))
    {
        printf("Error in sorting sequence!\n");
    }

    linked_list_my_struct_t_push(h, &data);
    linked_list_my_struct_t_push(h, &data2);
    linked_list_my_struct_t_push(h, &data3);
    linked_list_my_struct_t_push(h, &data4);

    if (linked_list_my_struct_t_get_length(h) != 4)
        printf("Error in length!\n");

    linked_list_my_struct_t_traverse(h, _print_node);

    out_data = linked_list_my_struct_t_pop(h);
    out_data2 = linked_list_my_struct_t_pop(h);
    out_data3 = linked_list_my_struct_t_pop(h);
    out_data4 = linked_list_my_struct_t_pop(h);

    if (linked_list_my_struct_t_get_length(h) != 0)
        printf("Error in length!\n");

    linked_list_my_struct_t_traverse(h, _print_node);
    

    if (!_cmp_eq(&out_data, &data4))
        printf("Error in push/pop routine!\n");
    if (!_cmp_eq(&out_data2, &data3))
        printf("Error in push/pop routine!\n");
    if (!_cmp_eq(&out_data3, &data2))
        printf("Error in push/pop routine!\n");
    if (!_cmp_eq(&out_data4, &data))
        printf("Error in push/pop routine!\n");

    linked_list_my_struct_t_append(h, &data);
    linked_list_my_struct_t_append(h, &data2);
    linked_list_my_struct_t_append(h, &data3);
    linked_list_my_struct_t_append(h, &data4);

    linked_list_my_struct_t_traverse(h, _print_node);

    out_data = linked_list_my_struct_t_pop(h);
    out_data2 = linked_list_my_struct_t_pop(h);
    out_data3 = linked_list_my_struct_t_pop(h);
    out_data4 = linked_list_my_struct_t_pop(h);

    if (!_cmp_eq(&out_data, &data))
        printf("Error in append/pop!\n");
    if (!_cmp_eq(&out_data2, &data2))
        printf("Error in append/pop!\n");
    if (!_cmp_eq(&out_data3, &data3))
        printf("Error in append/pop!\n");
    if (!_cmp_eq(&out_data4, &data4))
        printf("Error in append/pop!\n");
    
    linked_list_my_struct_t_traverse(h, _print_node);

    linked_list_my_struct_t_push(h, &data);
    linked_list_my_struct_t_append(h, &data2);
    linked_list_my_struct_t_push(h, &data3);
    linked_list_my_struct_t_push(h, &data3);
    linked_list_my_struct_t_insert_sorted(h, &data4);
    linked_list_my_struct_t_push(h, &data);

    my_struct_t new_data = { .a = 66, .b = 99 };
    linked_list_my_struct_t_insert_after(h, &new_data, 3);
    linked_list_my_struct_t_insert_after(h, &new_data, 0);
    linked_list_my_struct_t_insert_after(h, &new_data, 7);


    linked_list_my_struct_t_traverse(h, _print_node);

    my_struct_t out_new_data = linked_list_my_struct_t_peek(h);
    if (!_cmp_eq(&out_new_data, &data))
        printf("Peek failed!\n");
    
    out_new_data = linked_list_my_struct_t_get_at_pos(h, 1);
    if (!_cmp_eq(&out_new_data, &new_data))
        printf("get at pos failed\n");
    
    out_new_data = linked_list_my_struct_t_get_at_pos(h, 1);
    if (!_cmp_eq(&out_new_data, &data4))
        printf("get at pos failed\n");
    
    out_new_data = linked_list_my_struct_t_get_at_pos(h, 0);
    if (!_cmp_eq(&out_new_data, &data))
        printf("get at pos failed\n");

    out_new_data = linked_list_my_struct_t_get_at_pos(h, 5);
    if(!_cmp_eq(&out_new_data, &new_data))
        printf("get at pos failed\n");
    
    if (linked_list_my_struct_t_get_length(h) != 5)
        printf("length failed\n");  

    linked_list_my_struct_t_traverse(h, _increment);
    linked_list_my_struct_t_traverse(h, _print_node);

    // Create new linked list
    struct handle_my_struct_t handle2 = linked_list_my_struct_t_initialize();
    struct handle_my_struct_t *h2 = &handle2;

    my_struct_t dd = { .a = 32, .b = -12 };
    for (int i = 0; i < 10; i++)
        linked_list_my_struct_t_push(h2, &dd);
    
    linked_list_my_struct_t_traverse(h2, _print_node);

    
    
}

static void _my_struct_free(void *strct)
{
    // If the struct had been dynamically allocated, now would be the time to
    // free it
    free(strct);
}

static void _my_struct_deepcopy(my_struct_t *lhs, const my_struct_t* rhs)
{
    lhs->a = rhs->a;
    lhs->b = rhs->b;
}

static unsigned char _my_struct_cmp_lt(const my_struct_t *lhs, const my_struct_t *rhs)
{
    // You must decide what comparison makes sense for your structs
    if (lhs->a < rhs->a && lhs->b < rhs->b) return 1;
    return 0;
}
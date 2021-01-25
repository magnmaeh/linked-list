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
#include "example_double.h"

// Step 2. Define all the functions declared in the .h file
LINKED_LIST_GENERIC_DEFINE_ALL(double)

// Step 3. Implement these functions for your struct (if your struct needs them)
// Note: In some cases these functions simply reduce to the normal 'free()'
inline static void _double_free(void *strct);
static void _double_deepcopy(double *lhs, const double *rhs);

// Step 3.1 If you want to use 'linked_list_ _insert_sorted()', you must also
// implement a function that returns 1 if struct 1 < struct 2 (strict inequality).
static unsigned char _double_cmp_lt(const double *lhs, const double *rhs);

// For tests: linked_list_ _traverse()
static unsigned char _print_node(struct node_double *node)
{
    printf("------------------\n");
    printf("node->data = %f\n", *node->data);
    printf("------------------\n");
    return 0;
}

// For tests: linked_list_ _traverse()
static unsigned char _increment(struct node_double *node)
{
    *(node->data) = *(node->data) + 1;
    return 0;
}

// For tests: linked_list_ _insert_sorted()
static unsigned char _cmp_eq(const double *lhs, const double *rhs)
{
    if (*lhs != *rhs) return 0;
    return 1;
}


int double_test()
{
    /*** Initialization sequence begin ***/

    // Step 1. Initialize and save the handle the function returns
    struct handle_double handle = linked_list_double_initialize();
    struct handle_double *h = &handle;
    
    // Step 2. Set the handle's 'free()' and 'deepcopy()' with designated functions
    linked_list_double_set_free_func(h, _double_free);
    linked_list_double_set_deepcopy_func(h, _double_deepcopy);

    // Step 2.1 Set the handle's 'cmp_lt' with designated function
    linked_list_double_set_cmp_lt_func(h, _double_cmp_lt);

    /*** Initialization sequence end ***/

   
    // Tips and tricks
    /* 1. As a debugger, it would be a good idea to implement a function that 
          prints each node and pass it to 'linked_list_ _traverse()', which
          will execute that function on each node in your linked list.
       2. There is no limit on how many linked lists you initialize.
    */

    // Tests below
    double data = 12.321;
    double data2 = 92834;
    double data3 = 12.321;
    double data4 = 2.123;
   
    linked_list_double_insert_sorted(h, &data);
    linked_list_double_insert_sorted(h, &data2);
    linked_list_double_insert_sorted(h, &data3);
    linked_list_double_insert_sorted(h, &data4);

    if (linked_list_double_get_length(h) != 4)
        printf("Error in length!\n");

    linked_list_double_traverse(h, _print_node);

    double out_data = linked_list_double_pop(h);
    double out_data2 = linked_list_double_pop(h);
    double out_data3 = linked_list_double_pop(h);
    double out_data4 = linked_list_double_pop(h);

    if (linked_list_double_get_length(h) != 0)
        printf("Error in length!\n");

    linked_list_double_traverse(h, _print_node);

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

    linked_list_double_push(h, &data);
    linked_list_double_push(h, &data2);
    linked_list_double_push(h, &data3);
    linked_list_double_push(h, &data4);

    if (linked_list_double_get_length(h) != 4)
        printf("Error in length!\n");

    linked_list_double_traverse(h, _print_node);

    out_data = linked_list_double_pop(h);
    out_data2 = linked_list_double_pop(h);
    out_data3 = linked_list_double_pop(h);
    out_data4 = linked_list_double_pop(h);

    if (linked_list_double_get_length(h) != 0)
        printf("Error in length!\n");

    linked_list_double_traverse(h, _print_node);
    

    if (!_cmp_eq(&out_data, &data4))
        printf("Error in push/pop routine!\n");
    if (!_cmp_eq(&out_data2, &data3))
        printf("Error in push/pop routine!\n");
    if (!_cmp_eq(&out_data3, &data2))
        printf("Error in push/pop routine!\n");
    if (!_cmp_eq(&out_data4, &data))
        printf("Error in push/pop routine!\n");

    linked_list_double_append(h, &data);
    linked_list_double_append(h, &data2);
    linked_list_double_append(h, &data3);
    linked_list_double_append(h, &data4);

    linked_list_double_traverse(h, _print_node);

    out_data = linked_list_double_pop(h);
    out_data2 = linked_list_double_pop(h);
    out_data3 = linked_list_double_pop(h);
    out_data4 = linked_list_double_pop(h);

    if (!_cmp_eq(&out_data, &data))
        printf("Error in append/pop!\n");
    if (!_cmp_eq(&out_data2, &data2))
        printf("Error in append/pop!\n");
    if (!_cmp_eq(&out_data3, &data3))
        printf("Error in append/pop!\n");
    if (!_cmp_eq(&out_data4, &data4))
        printf("Error in append/pop!\n");
    
    linked_list_double_traverse(h, _print_node);

    linked_list_double_push(h, &data);
    linked_list_double_append(h, &data2);
    linked_list_double_push(h, &data3);
    linked_list_double_push(h, &data3);
    linked_list_double_insert_sorted(h, &data4);
    linked_list_double_push(h, &data2);

    double new_data = 9876.54321;
    linked_list_double_insert_after(h, &new_data, 3);
    linked_list_double_insert_after(h, &new_data, 0);
    linked_list_double_insert_after(h, &new_data, 7);


    linked_list_double_traverse(h, _print_node);

    double out_new_data = linked_list_double_peek(h);
    if (!_cmp_eq(&out_new_data, &data))
        printf("Peek failed!\n");
    
    out_new_data = linked_list_double_get_at_pos(h, 1);
    if (!_cmp_eq(&out_new_data, &new_data))
        printf("get at pos failed\n");
    
    out_new_data = linked_list_double_get_at_pos(h, 1);
    if (!_cmp_eq(&out_new_data, &data4))
        printf("get at pos failed\n");
    
    out_new_data = linked_list_double_get_at_pos(h, 0);
    if (!_cmp_eq(&out_new_data, &data))
        printf("get at pos failed\n");

    out_new_data = linked_list_double_get_at_pos(h, 5);
    if(!_cmp_eq(&out_new_data, &new_data))
        printf("get at pos failed\n");
    
    if (linked_list_double_get_length(h) != 5)
        printf("length failed\n");  

    printf("=======\n");
    printf("Length = %d\n", linked_list_double_get_length(h));

    linked_list_double_traverse(h, _increment);
    linked_list_double_traverse(h, _print_node);


    struct handle_double handle2 = linked_list_double_initialize();
    struct handle_double *h2 = &handle2;
    
    linked_list_double_set_free_func(h2, _double_free);
    linked_list_double_set_deepcopy_func(h2, _double_deepcopy);

    double data_arr[10];
    for (int i = 0; i < 10; i++)
    {
        data_arr[i] = 10.0;
        linked_list_double_push(h2, &data_arr[i]);
    }
    
    linked_list_double_traverse(h2, _increment);
    linked_list_double_traverse(h2, _print_node);

}

inline static void _double_free(void *strct)
{
    free(strct);
}

static void _double_deepcopy(double *lhs, const double* rhs)
{
    *lhs = *rhs;
}

static unsigned char _double_cmp_lt(const double *lhs, const double *rhs)
{
    if (*lhs < *rhs) return 1;
    return 0;
}
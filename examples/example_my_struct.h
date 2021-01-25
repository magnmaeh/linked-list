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

#ifndef EXAMPLE_MY_STRUCT_H
#define EXAMPLE_MY_STRUCT_H

// Step 1. Include the linked_list_declarations.h file
#include "../inc/linked_list_declarations.h"

// Step 2. Define struct to generate linked list functions for
// Note: It must be typedefed
typedef struct my_struct
{
    int a;
    int b;
} my_struct_t;

// Step 3. Define a node using the macro below
LINKED_LIST_GENERIC_DEFINE_NODE(my_struct_t)

// Step 4. Define a meta (which acts as a read-only handle for your linked list)
LINKED_LIST_GENERIC_DEFINE_HANDLE(my_struct_t)

// Step 5. Declare all functions associated with the linked list
LINKED_LIST_GENERIC_DECLARE_ALL(my_struct_t)

#endif
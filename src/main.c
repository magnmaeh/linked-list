#include "linked_list_declarations.h"
#include "linked_list_definitions.h"
#include <stddef.h>
#include <stdio.h>


static void (*_free_function[LINKED_LIST_MAX_LISTS])(void*) = {0};
static struct node_my_struct **_my_struct_head[LINKED_LIST_MAX_LISTS] = {0};
static unsigned char _linked_list_length[LINKED_LIST_MAX_LISTS] = {0};
static unsigned char _list_index = 0;

LINKED_LIST_GENERIC_DEFINE_ALL(my_struct)


/*static unsigned char _setter_double(struct node_double* node, double* data);
static unsigned char _printer(struct node_double *node);
static unsigned char _cmp_lt_double(const double *d1, const double *d2);
static void test_double();*/

static unsigned char _setter_my_struct(struct node_my_struct *node, my_struct *data)
{
    node->data = data;
    node->next = NULL;
    return 0;
}

static unsigned char _printer(struct node_my_struct *node)
{
    printf("----------\n");
    printf("node->data->a = %d\n", node->data->a);
    printf("node->data->b = %d\n", node->data->b);
    printf("----------\n");
    return 0;
}

static unsigned char _cmp_lt_my_struct(const my_struct *m1, const my_struct *m2)
{
    if (m1->a < m2->a && m1->b < m2->b)
        return 1;
    return 0;
}

static void _free_my_struct(void *data)
{
    free(data);
}

int main() {
    linked_list_my_struct_initialize();
    linked_list_my_struct_set_free_func(_free_my_struct);

    my_struct m1 = { .a = 10, .b = 15 };
    linked_list_my_struct_push(&m1);
    linked_list_my_struct_push(&m1);
    linked_list_my_struct_push(&m1);

    linked_list_my_struct_print(_printer);

    linked_list_my_struct_set_list_index(1);
    linked_list_my_struct_initialize();
    linked_list_my_struct_set_free_func(_free_my_struct);

    my_struct m2 = { .a = 22, .b = 21 };
    my_struct m3 = { .a = 1, .b = 2 };
    linked_list_my_struct_insert_sorted(&m2, _cmp_lt_my_struct);
    linked_list_my_struct_insert_sorted(&m3, _cmp_lt_my_struct);
    linked_list_my_struct_insert_sorted(&m1, _cmp_lt_my_struct);

    linked_list_my_struct_print(_printer);

    linked_list_my_struct_set_list_index(0);
    linked_list_my_struct_print(_printer);

    linked_list_my_struct_set_list_index(2);
    linked_list_my_struct_print(_printer);

    linked_list_my_struct_set_list_index(1);

    my_struct m4 = linked_list_my_struct_pop();
    linked_list_my_struct_set_list_index(2);
    linked_list_my_struct_initialize();
    linked_list_my_struct_set_free_func(_free_my_struct);

    my_struct m5 = { .a = 13, .b = 66 };
    linked_list_my_struct_push(&m4);

    linked_list_my_struct_print(_printer);



    return 0;
}









/*static unsigned char _setter_double(struct node_double* node, double* data)
{
    node->data = data;
    node->next = NULL;
    return 0;
}

static unsigned char _printer(struct node_double *node)
{
    printf("----------\n");
    printf("Node = %d\n", node);
    printf("Node data = %f\n", *node->data);
    printf("----------\n");
    return 0;
}

static unsigned char _cmp_lt_double(const double *d1, const double *d2)
{
    return *d1 < *d2;
}

static void test_double()
{
    linked_list_double_initialize();

    linked_list_double_set_free_func(free);

    double data = 12.2;

    linked_list_double_push(&data);
    linked_list_double_push(&data);
    linked_list_double_push(&data);

    linked_list_double_print(_printer);

    linked_list_double_set_list_index(2);

    linked_list_double_set_free_func(free);

    linked_list_double_initialize();

    double data2 = 15;

    linked_list_double_push(&data2);
    linked_list_double_push(&data2);

    linked_list_double_print(_printer);

    linked_list_double_set_list_index(0);

    linked_list_double_print(_printer);

    linked_list_double_pop();
    linked_list_double_pop();
    linked_list_double_pop();
    linked_list_double_pop();

    linked_list_double_print(_printer);
}*/
/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** concat_arr.c
*/

#include "unistd.h"
#include "stdlib.h"

int get_arr_len(void **arr);

void concat_arr(void ***a1, void **a2)
{
    void **tmp1 = *a1;
    void **tmp2 = a2;
    void **res;
    int len_1 = get_arr_len(*a1);
    int len_2 = get_arr_len(tmp2);

    if (!a2)
        return;
    res = malloc(sizeof(void *) * (len_1 + len_2 + 1));
    for (int i = 0; i < len_1; i++)
        res[i] = tmp1[i];
    for (int i = 0; i < len_2; i++)
        res[i + len_1] = tmp2[i];
    res[len_1 + len_2] = NULL;
    *a1 = res;
    return;
}

void append_arr(void ***a1, void *a2)
{
    void **tmp1 = *a1;
    void **res;
    int len_1 = get_arr_len(*a1);

    if (!a2)
        return;
    res = malloc(sizeof(void *) * (len_1 + 2));
    for (int i = 0; i < len_1; i++)
        res[i] = tmp1[i];
    res[len_1] = a2;
    res[len_1 + 1] = NULL;
    free(*a1);
    *a1 = res;
    return;
}

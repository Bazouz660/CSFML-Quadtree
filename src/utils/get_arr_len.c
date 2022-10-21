/*
** EPITECH PROJECT, 2022
** SpageGameRepo
** File description:
** get_arr_len.c
*/

#include "includes.h"

int get_arr_len(void **arr)
{
    int i = 0;

    if (arr == NULL)
        return 0;
    for (i = 0; arr[i] != NULL; i++);
    return i;
}

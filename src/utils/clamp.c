/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** clamp.c
*/

double clamp(double min, double max, double value)
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

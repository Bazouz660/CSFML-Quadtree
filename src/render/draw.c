/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** draw.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"

static void draw_entities(core_t *c)
{
    entity_t *tmp = c->entities;

    while (tmp) {
        sfRenderWindow_drawRectangleShape(c->render.window, tmp->shape, NULL);
        sfRectangleShape_setFillColor(tmp->shape, sfRed);
        tmp = tmp->next;
    }
}

static void draw_quadtree(core_t *c, quadtree_t *qt)
{
    sfRenderWindow_drawRectangleShape(c->render.window, qt->shape, NULL);
    if (!qt->divided)
        return;
    draw_quadtree(c, qt->nw);
    draw_quadtree(c, qt->ne);
    draw_quadtree(c, qt->sw);
    draw_quadtree(c, qt->se);
}

void draw_all(core_t *c)
{
    draw_quadtree(c, c->quadtree);
    if (c->render.boxes_visible)
        draw_entities(c);
    sfRenderWindow_drawRectangleShape(c->render.window, c->range, NULL);
    sfRenderWindow_drawText(c->render.window, c->render.fps_hint, NULL);
}

/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** quadtree.c
*/

#include "prototypes.h"

bool frect_countains_frect(sfFloatRect r1, sfFloatRect r2)
{
    if (r2.left > r1.left && r2.left + r2.width < r1.left + r1.width
        && r2.top > r1.top && r2.top + r2.height < r1.top + r1.height)
        return true;
    return false;
}

void subdivide(quadtree_t *pa)
{
    sfVector2f pos = pa->pos;
    sfVector2f size = pa->size;

    pa->nw = new_quadtree(vect_mult(pa->size, 0.5),
    (sfVector2f){pos.x - (size.x / 4.0), pos.y - (size.y / 4.0)},
    pa->capacity, pa->deepness + 1, sfYellow, pa);
    pa->ne = new_quadtree(vect_mult(pa->size, 0.5),
    (sfVector2f){pos.x + (size.x / 4.0), pos.y - (size.y / 4.0)},
    pa->capacity, pa->deepness + 1, sfGreen, pa);
    pa->sw = new_quadtree(vect_mult(pa->size, 0.5),
    (sfVector2f){pos.x - (size.x / 4.0), pos.y + (size.y / 4.0)},
    pa->capacity, pa->deepness + 1, sfRed, pa);
    pa->se = new_quadtree(vect_mult(pa->size, 0.5),
    (sfVector2f){pos.x + (size.x / 4.0), pos.y + (size.y / 4.0)},
    pa->capacity, pa->deepness + 1, sfBlue, pa);
}

quadtree_t *new_quadtree(sfVector2f size, sfVector2f pos,
int capacity, int deepness, sfColor color, quadtree_t *parent)
{
    quadtree_t *qt = malloc(sizeof(quadtree_t));

    qt->entities = malloc(sizeof(entity_t *) * (capacity + 1));
    qt->capacity = capacity;
    qt->deepness = deepness;
    qt->parent = parent;
    qt->size = size;
    qt->full = false;
    qt->divided = false;
    qt->fullness = 0;
    qt->pos = pos;
    qt->ne = NULL;
    qt->nw = NULL;
    qt->se = NULL;
    qt->sw = NULL;
    qt->shape = sfRectangleShape_create();
    sfRectangleShape_setFillColor(qt->shape, sfTransparent);
    sfRectangleShape_setOutlineColor(qt->shape, color);
    sfRectangleShape_setOutlineThickness(qt->shape, 1);
    sfRectangleShape_setSize(qt->shape, size);
    sfRectangleShape_setOrigin(qt->shape, get_rect_center(qt->shape));
    sfRectangleShape_setPosition(qt->shape, pos);
    return qt;
}

bool insert_entity(quadtree_t *qt, entity_t *entity, int corner)
{
    sfFloatRect entity_box = sfRectangleShape_getGlobalBounds(entity->shape);
    sfFloatRect leaf_box = sfRectangleShape_getGlobalBounds(qt->shape);
    bool inserted = false;


    if (!frect_countains_frect(leaf_box, entity_box) && qt->parent) {
        return false;
    }
    if (qt->fullness + 1 < qt->capacity) {
        qt->entities[qt->fullness] = entity;
        qt->fullness++;
        return true;
    } else if (!qt->divided) {
        subdivide(qt);
        qt->divided = true;
    }
    inserted |= insert_entity(qt->nw, entity, 1);
    inserted |= insert_entity(qt->ne, entity, 2);
    inserted |= insert_entity(qt->sw, entity, 3);
    inserted |= insert_entity(qt->se, entity, 4);
    if (inserted)
        return true;
    if (frect_countains_frect(leaf_box, entity_box) || !(qt->parent)) {
        if (qt->fullness >= qt->capacity)
            qt->entities = realloc(qt->entities, sizeof(entity_t *) * (qt->fullness + 1));
        qt->entities[qt->fullness] = entity;
        qt->fullness++;
        return true;
    } else {
        insert_entity(qt->parent, entity, 0);
    }
}

void free_quadtree(quadtree_t *qt)
{
    if (qt->divided) {
        free_quadtree(qt->nw);
        free_quadtree(qt->ne);
        free_quadtree(qt->sw);
        free_quadtree(qt->se);
        free(qt->nw);
        free(qt->ne);
        free(qt->sw);
        free(qt->se);
    }
    free(qt->entities);
    sfRectangleShape_destroy(qt->shape);
}

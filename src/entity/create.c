/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** create.c
*/

#include "structs.h"
#include "includes.h"
#include "structs.h"
#include "prototypes.h"

entity_t *new_entity(core_t *c, sfVector2f pos)
{
	entity_t *entity = malloc(sizeof(entity_t));

	entity->shape = sfRectangleShape_create();

    sfRectangleShape_setFillColor(entity->shape, sfRed);
	sfRectangleShape_setSize(entity->shape, (sfVector2f){random_number(10, 200)
	, random_number(10, 50)});
	sfRectangleShape_setOrigin(entity->shape, get_rect_center(entity->shape));
	sfRectangleShape_setPosition(entity->shape, pos);
	return entity;
}

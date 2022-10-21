/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** actions.c
*/

#include "prototypes.h"

void toggle_fullscreen(core_t *c, switch_key_t *key)
{
    c->render.fullscreen = key->state;
    sfRenderWindow_close(c->render.window);
    sfRenderWindow_destroy(c->render.window);
    c->render.window = create_window("Backrooms", key->state);
}

void place_rect(core_t *c, switch_key_t *key)
{
    add_entity(c, &c->entities, v2i_to_v2f(c->mouse.pos));
}

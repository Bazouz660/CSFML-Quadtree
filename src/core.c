/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** core.c
*/

#include "includes.h"
#include "structs.h"
#include "prototypes.h"
#include "defines.h"

void close_game(core_t *c)
{
    sfRenderWindow_close(c->render.window);
}

void analyse_events(core_t *c)
{
    int mouse_released = 0;

    while (sfRenderWindow_pollEvent(c->render.window, &c->events.input)) {
        update_toggleable_keys(c);
        if (c->events.input.type == sfEvtMouseButtonReleased)
            mouse_released += 1;
        if (c->events.input.type == sfEvtClosed ||
            sfKeyboard_isKeyPressed(sfKeyEscape))
            close_game(c);
    }
}

void update_mouse(core_t *c)
{
    c->mouse.lastpos = c->mouse.pos;
    c->mouse.pos = get_mouse_pos_view(c);
    c->mouse.diff.x = c->mouse.pos.x - c->mouse.lastpos.x;
    c->mouse.diff.y = c->mouse.pos.y - c->mouse.lastpos.y;
}

void update_quadtree(core_t *c)
{
    entity_t *tmp = c->entities;

    free_quadtree(c->quadtree);
    free(c->quadtree);
    c->quadtree = new_quadtree(v2u_to_v2f(c->render.w_size),
    sfView_getCenter(c->render.view), 10, 0, sfWhite, NULL);

    while (tmp) {
        insert_entity(c->quadtree, tmp, 0);
        tmp = tmp->next;
    }
}

void render_game(core_t *c)
{
    update_quadtree(c);

    sfFloatRect range = sfRectangleShape_getGlobalBounds(c->range);

    qt_range(c, c->quadtree, range);

    query_t *found = c->query;

    while (found) {
        sfRectangleShape_setFillColor(found->entity->shape, sfGreen);
        found = found->next;
    }
    free_query(c->query);
    c->query = NULL;

    if (sfMouse_isButtonPressed(sfMouseLeft))
        sfRectangleShape_setPosition(c->range, (sfVector2f){c->mouse.pos.x, c->mouse.pos.y});
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        sfRectangleShape_setSize(c->range, (sfVector2f){range.width, range.height + 1});
    if (sfKeyboard_isKeyPressed(sfKeyUp))
        sfRectangleShape_setSize(c->range, (sfVector2f){range.width, range.height - 1});
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        sfRectangleShape_setSize(c->range, (sfVector2f){range.width + 1, range.height});
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        sfRectangleShape_setSize(c->range, (sfVector2f){range.width - 1, range.height});
    if (sfKeyboard_isKeyPressed(sfKeyE))
        add_entity(c, &c->entities, v2i_to_v2f(c->mouse.pos));
    draw_all(c);
}

int game_loop(void)
{
    core_t *c = malloc(sizeof(core_t));

    init_game(c);
    sfRenderWindow_setVerticalSyncEnabled(c->render.window, True);
    //sfRenderWindow_setFramerateLimit(c->render.window, 150);
    while (sfRenderWindow_isOpen(c->render.window)) {
        update_clock(c);
        update_fps(c);
        update_screen(c);
        update_mouse(c);
        render_game(c);
        analyse_events(c);
    }
    return 0;
}

int main(int ac, char **av)
{
    return game_loop();
}

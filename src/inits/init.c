/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** init.c
*/

#include "inputs.h"
#include "structs.h"
#include "prototypes.h"

void init_fps_text(core_t *c)
{
    c->render.font = sfFont_createFromFile("misc/font.ttf");
    c->render.fps_hint = sfText_create();
    sfText_setFont(c->render.fps_hint, c->render.font);
    sfText_setColor(c->render.fps_hint, sfWhite);
    sfText_setPosition(c->render.fps_hint, (sfVector2f){c->render.w_size.x / 30.0,
    c->render.w_size.y / 25.0});
    sfText_setString(c->render.fps_hint, NULL);
    sfText_setOutlineColor(c->render.fps_hint, sfBlack);
    sfText_setOutlineThickness(c->render.fps_hint, 1);
    sfText_setCharacterSize(c->render.fps_hint, c->render.w_size.x / 40);
}

void init_view(core_t *c)
{
    sfVector2u w_size = sfRenderWindow_getSize(c->render.window);
    c->render.view = sfView_create();
    sfView_setSize(c->render.view, (sfVector2f){w_size.x,
    w_size.y});
    sfView_setViewport(c->render.view, (sfFloatRect){0, 0, 0.3, 0.3});
    sfView_setCenter(c->render.view, sfView_getCenter(sfRenderWindow_getView(c->render.window)));
}

void init_mouse(core_t *c)
{
    c->mouse.pos = get_mouse_pos_view(c);
}

void init_keys(core_t *c)
{
    c->events.keys.toggleable = malloc(sizeof(switch_key_t) * (4));
    init_toggleable_key(&c->events.keys.toggleable[0], sfKeyF11,
    &toggle_fullscreen);
    init_toggleable_key(&c->events.keys.toggleable[1], sfKeyE,
    &place_rect);
    init_toggleable_key(&c->events.keys.toggleable[2], sfKeyV,
    &toggle_boxes_visible);
    c->events.keys.toggleable[3].index = -1;
}

void init_quadtree(core_t *c)
{
    c->quadtree = new_quadtree(v2u_to_v2f(c->render.w_size),
    sfView_getCenter(c->render.view), 10, 0, sfWhite, NULL);
}

void init_range(core_t *c)
{
    c->range = sfRectangleShape_create();

    sfRectangleShape_setFillColor(c->range, TransparentRed);
    sfRectangleShape_setSize(c->range, (sfVector2f){0, 0});
    sfRectangleShape_setPosition(c->range, (sfVector2f){0, 0});
}

void init_game(core_t *c)
{
    c->render.window = create_window("Backrooms", false);
    c->render.w_size = sfRenderWindow_getSize(c->render.window);
    sfRenderWindow_setPosition(c->render.window, (sfVector2i){0, 0});
    c->clock.clock = sfClock_create();
    c->mouse.lastpos = get_mouse_pos_view(c);
    c->mouse.diff = (sfVector2i){0, 0};
    c->clock.prev_time.microseconds = 0;
    c->clock.frame_delta = 0;
    c->entities = NULL;
    c->query = NULL;
    c->render.boxes_visible = true;
    srand(time(NULL));
    init_view(c);
    init_mouse(c);
    init_keys(c);
    init_fps_text(c);
    init_quadtree(c);
    init_range(c);
}

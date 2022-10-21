/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** structs.h
*/

#include "defines.h"
#include "includes.h"

#ifndef QUADTREE_STRUCTS
    #define QUADTREE_STRUCTS

    typedef struct core_s core_t;

    typedef struct matrix_s {
        int rows;
        int cols;
        float **data;
    } matrix_t;

    typedef struct switch_key_s {
        int index;
        bool prev_state;
        bool can_press;
        bool state;
        sfKeyCode keycode;
        void (*do_action)(core_t *, struct switch_key_s *);
        void (*update)(core_t *, struct switch_key_s *);
    } switch_key_t;

    typedef struct render_s {
        sfRenderWindow *window;
        sfVector2u w_size;
        sfView *view;
        sfText *fps_hint;
        sfFont *font;
        bool fullscreen;
        bool boxes_visible;
    } render_t;

    typedef struct clock_s {
        sfClock *clock;
        sfTime time;
        sfTime prev_time;
        float frame_delta;
        float elapsed_time;
        float seconds;
    } clock_st;

    typedef struct mouse_s {
        sfVector2i pos;
        sfVector2i lastpos;
        sfVector2i diff;
    } mouse_t;

    typedef struct keys_s {
        switch_key_t *toggleable;
    } keys_t;

    typedef struct events_s {
        sfEvent input;
        keys_t keys;
    } events_t;

    typedef struct entity_s {
        int index;
        sfRectangleShape *shape;
        struct entity_s *next;
        struct entity_s *prev;
    } entity_t;

    typedef struct quadtree_s {
        entity_t **entities;
        int capacity;
        int fullness;
        int deepness;
        bool full;
        bool divided;
        sfVector2f size;
        sfVector2f pos;
        sfRectangleShape *shape;
        struct quadtree_s *parent;
        struct quadtree_s *nw;
        struct quadtree_s *ne;
        struct quadtree_s *sw;
        struct quadtree_s *se;
    } quadtree_t;

    typedef struct query_s {
        int index;
        entity_t *entity;
        struct query_s *next;
        struct query_s *prev;
    } query_t;

    struct core_s {
        render_t render;
        clock_st clock;
        entity_t *entities;
        events_t events;
        mouse_t mouse;
        quadtree_t *quadtree;
        query_t *query;
        sfRectangleShape *range;
    };

#endif /*QUADTREE_STRUCTS*/

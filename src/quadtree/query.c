/*
** EPITECH PROJECT, 2022
** quadtree2
** File description:
** query.c
*/

#include "prototypes.h"

void add_node(query_t **head, entity_t *entity)
{
	static int index = 0;
	query_t *nnode = malloc(sizeof(query_t));

	nnode->index = index;
    nnode->entity = entity;
	nnode->next = (*head);
	nnode->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = nnode;
	(*head) = nnode;
	index++;
}

void del_node(query_t **head, query_t *del_node)
{
	if (*head == NULL || del_node == NULL)
		return ;
	if (*head == del_node)
		*head = del_node->next;
	if (del_node->next != NULL)
		del_node->next->prev = del_node->prev;
	if (del_node->prev != NULL)
		del_node->prev->next = del_node->next;
	free(del_node);
}

void free_query(query_t *list)
{
    query_t *tmp = list;
    query_t *tampon;

    while (tmp != NULL) {
        tampon = tmp->next;
        free(tmp);
        tmp = tampon;
    }
}

void qt_range(core_t *c, quadtree_t *qt, sfFloatRect range)
{
    sfFloatRect leaf_box = sfRectangleShape_getGlobalBounds(qt->shape);
    sfFloatRect entity_box;

    if (!sfFloatRect_intersects(&leaf_box, &range, NULL))
        return;
    for (int i = 0; i < qt->fullness; i++) {
        entity_box = sfRectangleShape_getGlobalBounds(qt->entities[i]->shape);
        if (sfFloatRect_intersects(&entity_box, &range, NULL)) {
            add_node(&c->query, qt->entities[i]);
        }
    }
    if (qt->divided) {
        qt_range(c, qt->nw, range);
        qt_range(c, qt->ne, range);
        qt_range(c, qt->sw, range);
        qt_range(c, qt->se, range);
    }
}

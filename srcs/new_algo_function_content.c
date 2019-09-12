/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo_function_content.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:39:36 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/12 13:39:38 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				next_is_it_trigger(t_god *god, int room, int last_one)
{
	int i;

	i = 0;
	while (i < god->rooms[room]->nb_of_connexions)
	{
		if (god->rooms[room]->connexions[i]->id != god->rooms[room]->id
		&& god->rooms[room]->connexions[i]->id != god->extremities[0]->id
		&& god->rooms[room]->blocked == 1
		&& is_it_connected(god, room, god->rooms[room]->connexions[i]->id) == 1)
			return (1);
		i++;
	}
	return (0);
}

int				basic_test_do_trigger(t_god *god, t_lemin *room, int i, int j)
{
	if (room->tmp_used[j] == 0
		&& room->connexions[j]->gone == 1
		&& room->id != god->extremities[0]->id
		&& room->connexions[j]->id != god->extremities[0]->id
		&& room->blocked == 1
		&& room->connexions[j]->id != room->last_room->id
		&& is_it_connected(god, room->id, room->connexions[j]->id) == 1)
		return (1);
	else
		return (0);
}

void			do_the_trigger(t_lemin *room, t_ints tab, int i, int j)
{
	int nb;

	tab[0] = tab[0] + 1;
	nb = tab[0];
	tab[nb] = room->connexions[j]->id;
	room->connexions[j]->weight = room->weight - 1;
	room->connexions[j]->last_room = room;
	room->surcharged = 1;
}

int				test_g_one(t_god *god, t_lemin *room, int i, int j)
{
	if (room->connexions[j]->gone == 1
	&& room->tmp_used[j] == 0
	&& room->connexions[j]->id != god->extremities[0]->id
	&& room->last_room != NULL
	&& room->connexions[j]->id != room->last_room->id
	&& is_it_connected(god, room->id, room->connexions[j]->id) == 0
	&& ((room->nb_of_connexions == 2
	&& next_is_it_trigger(god, room->connexions[j]->id, room->id) == 1)
	|| room->last_room->surcharged == 1)
	&& ((room->weight + 1 <= room->connexions[j]->weight)
	|| room->connexions[j]->weight == 0))
		return (1);
	return (0);
}

int				zero_tst(t_god *god, t_lemin *room, int i, int j)
{
	if (room->connexions[j]->gone == 0 && room->tmp_used[j] == 0
	&& room->connexions[j]->id != god->extremities[0]->id
	&& room->surcharged == 0)
		return (1);
	else
		return (0);
}

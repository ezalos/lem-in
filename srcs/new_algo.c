/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:52:16 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/11 16:34:15 by ythomas          ###   ########.fr       */
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

void			check_possible_trigger(t_god *god,
		t_ints last_p, t_piles *stack)
{
	int i;
	int j;

	i = 0;
	while (i < last_p[0])
	{
		j = 0;
		while (j < god->rooms[last_p[i + 1]]->nb_of_connexions)
		{
			stack->actual_room = god->rooms[last_p[i + 1]]->id;
			if (basic_test_do_trigger(god, god->rooms[last_p[i + 1]], i, j) == 1
				&& ((god->rooms[last_p[i + 1]]->last_room->surcharged != 1)
				|| ((god->rooms[last_p[i + 1]]->last_room->surcharged == 1)
				&& (god->rooms[last_p[i + 1]]->nb_of_connexions == 2))))
			{
				do_the_trigger(god->rooms[last_p[i + 1]], last_p, i, j);
				(god->trigger)++;
			}
			j++;
		}
		i++;
	}
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

int				get_next_rooms(t_god *god, t_piles *stack,
	t_ints lp, t_ints new_p)
{
	int i[2];

	if (++stack->deep && lp[0] == 0)
		return (stack->finish = 2);
	check_possible_trigger(god, lp, stack);
	i[0] = -1;
	while (++i[0] < lp[0])
	{
		i[1] = -1;
		while (++i[1] < god->rooms[lp[i[0] + 1]]->nb_of_connexions)
		{
			stack->actual_room = god->rooms[lp[i[0] + 1]]->id;
			if (test_g_one(god, god->rooms[lp[i[0] + 1]], i[0], i[1]) == 1)
				gone_is_one(god, stack, new_p,
				god->rooms[lp[i[0] + 1]]->connexions[i[1]]->id);
			else if (zero_tst(god, god->rooms[lp[i[0] + 1]], i[0], i[1]) == 1)
			{
				gone_is_zero(god, stack, new_p,
				god->rooms[lp[i[0] + 1]]->connexions[i[1]]->id);
				if (stack->finish == 1)
					return (1);
			}
		}
	}
	return (stack->finish);
}

int				get_faster_path(t_god *god)
{
	t_piles stack;

	init_stack(god->size * 2, &stack, god->extremities[0]->id);
	while (stack.finish == 0)
	{
		if (stack.deep % 2 == 0)
		{
			get_next_rooms(god, &stack, stack.pile_a, stack.pile_b);
			stack.pile_a[0] = 0;
		}
		else if (stack.deep % 2 != 0)
		{
			get_next_rooms(god, &stack, stack.pile_b, stack.pile_a);
			stack.pile_b[0] = 0;
		}
	}
	return (stack.finish);
}

int				breadth_first_search(t_god *god, int *stat)
{
	int			nb_finish;
	int			nb;

	nb_finish = 0;
	while (nb_finish < god->goulots && *stat != 2)
	{
		if ((*stat = get_faster_path(god)) == 1)
		{
			add_path_to_set(god, nb_finish);
			nb_finish++;
			if (which_link_is_surcharged(god, god->paths[nb_finish - 1]) == 1)
				nb_finish = reset_this_set(god, nb_finish);
			else
			{
				if (nb_finish == god->variation &&
				(nb = ft_evaluate_set_of_path(god, nb_finish)) < god->turn)
					save_actual_set(god, nb_finish, nb);
				else if (nb_finish == god->variation && nb > god->turn)
					break ;
			}
		}
		clear_gone(god);
		refresh_tmp_links(god);
		add_gone(god, nb_finish);
	}
	return (nb_finish);
}

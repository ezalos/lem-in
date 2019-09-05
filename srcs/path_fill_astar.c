/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fill_astar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:05:17 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:48:09 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				execute_pile(t_god *god, t_piles *stack,
	t_ints pile_a, t_ints pile_b)
{
	t_lemin		*lem_in;
	int				*a;
	int				*b;
	int				i;

	a = (void*)pile_a;
	b = (void*)pile_b;
	stack->r_v = 0;
	while (*a > 0)
	{
		lem_in = god->rooms[pile_a[*a]];
		if (!lem_in || lem_in->gone)
			pile_a[(*a)--] = 0;
		if (lem_in->id == stack->finish)
			stack->r_v++;
		if (!lem_in->from[stack->ste])
		{
			lem_in->from[stack->ste] = stack->deep;
			i = -1;
			while (lem_in->connexions[++i])
					pile_b[++(*b)] = ((t_lemin*)lem_in->connexions[i])->id;
		}
		pile_a[(*a)--] = 0;
	}
	return (stack->r_v);
}

int				alternate_piles(t_god *god, int id_start,
	int id_end, int start_to_end)
{
	t_piles stack;
	int 	depth;
	int		r_v;

	depth = 0;
	init_stack(god->size * 2, &stack, id_start);
	stack.finish = id_end;
	stack.ste = start_to_end;
	r_v = 0;
	while (stack.pile_a[0] || stack.pile_b[0])
	{
		if (stack.deep % 2)
			r_v += execute_pile(god, &stack, stack.pile_a, stack.pile_b);
		else
			r_v += execute_pile(god, &stack, stack.pile_b, stack.pile_a);
		stack.deep++;
	}
	return (r_v);
}

int				refresh_a_star(t_god *god)
{
	int r_v;

	r_v = 0;
	clear_data(god);
	r_v = alternate_piles(god, god->end->id, god->start->id, 1);
	god->end->from[1] = 0;
	return (r_v);
}

int			is_there_a_path(t_god *god, int *kill_list,
	int point_a, int point_b)
{
	int r_v;
	int	i;

	r_v = 0;
	clear_data(god);
	i = -1;
	if (kill_list)
		kill_list = NULL;
	god->end->gone = 1;
	god->start->gone = 1;
	r_v = alternate_piles(god, god->rooms[point_a]->id,
		god->rooms[point_b]->id, 0);
	god->end->gone = 0;
	god->start->gone = 0;
	i = -1;
	i++;
	clear_data(god);
	return (r_v);
}

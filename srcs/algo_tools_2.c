/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:08:52 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/05 13:08:53 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void 			add_gone(t_god *god, int nb_paths)
{
	int i;
	int j;
	int size;

	i = 0;
	while (i < nb_paths)
	{
		j = 1;
		size = god->paths[i][0];
		if (size != 0)
			while (j <= size)
			{
				god->rooms[god->paths[i][j]]->gone = 1;
				god->rooms[god->paths[i][j]]->blocked = 1;
				if (god->rooms[god->paths[i][j]]->last_room != NULL)
					god->rooms[god->paths[i][j]]
					->tmp_used[find_link(god->rooms[god->paths[i][j]])] = 1;
				j++;
			}
		i++;	
	}
}

void			gone_is_zero(t_god *god, t_piles *stack, t_ints new_p, int id)
{
	int nb;

	god->rooms[id]->weight = god->rooms[stack->actual_room]->weight + 1;
	god->rooms[id]->last_room = god->rooms[stack->actual_room];
	if (id == god->extremities[1]->id)
	{
		stack->finish = 1;
		return ;
	}
	god->rooms[stack->actual_room]
	->tmp_used[find_pv_link(god, god->rooms[id], stack)] = 1;
	god->rooms[id]->gone = 1;
	new_p[0] = new_p[0] + 1;
	nb = new_p[0];
	new_p[nb] = id;
}

void			gone_is_one(t_god *god, t_piles *stack, t_ints new_p, int id)
{
	int nb;

	if (god->rooms[id]->weight >= god->rooms[stack->actual_room]->weight + 1
	|| god->rooms[id]->weight == 0)
	{
		god->rooms[id]->last_room = god->rooms[stack->actual_room];
		god->rooms[id]->weight = god->rooms[id]->last_room->weight + 1;
	}
	god->rooms[stack->actual_room]
	->tmp_used[find_pv_link(god, god->rooms[id], stack)] = 1;
	new_p[0] = new_p[0] + 1;
	nb = new_p[0];
	new_p[nb] = id;
}

void			init_stack(int size, t_piles *stack, int id)
{
	stack->pile_a = ft_memalloc(sizeof(t_ints) * size * 2);
	stack->pile_b = ft_memalloc(sizeof(t_ints) * size * 2);
	stack->pile_a[0] = 1;
	stack->pile_a[1] = id;
	stack->finish = 0;
	stack->deep = 0;
	stack->actual_room = 0;
}

int				reset_this_set(t_god *god, int nb_finish)
{
	int i;
	int len;
	int j;

	i = 0;
	while (i < nb_finish)
	{
		len = god->paths[i][0];
		j = 0;
		while (j <= len)
		{
			god->paths[i][j] = 0;
			j++;
		}
		i++;
	}
	clear_links(god);
	return (0);
}

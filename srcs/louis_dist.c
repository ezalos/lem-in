/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_dist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:56:10 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/12 12:56:12 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/head.h"

void			ft_execute_pile_end_to_start(t_god *god, int depth,
	t_ints pile_a, t_ints pile_b)
{
	t_lemin		*lem_in;
	int				*a;
	int				*b;
	int				i;

	a = (void*)pile_a;
	b = (void*)pile_b;
	while (*a > 0)
	{
		lem_in = god->rooms[pile_a[*a]];
		if (!lem_in || lem_in->gone)
			pile_a[(*a)--] = 0;
		else if (lem_in->id == god->extremities[0]->id)//is it start
		{
			if (!lem_in->dist_to_end || lem_in->dist_to_end > depth)
			{
				lem_in->dist_to_end = depth;
				lem_in->orientation = depth;
			}
		}
		else if (!lem_in->dist_to_end)
		{
			lem_in->dist_to_end = depth;
			lem_in->orientation = depth;
			i = -1;
			while (lem_in->connexions[++i])
					pile_b[++(*b)] = ((t_lemin*)lem_in->connexions[i])->id;
		}
		pile_a[(*a)--] = 0;
	}
}

void			get_dist_from_end(t_god *god)
{
	t_ints	pile_a;
	t_ints	pile_b;
	int 	depth;

	depth = 0;
	pile_a = ft_memalloc(sizeof(t_ints) * god->size * 2);
	pile_b = ft_memalloc(sizeof(t_ints) * god->size * 2);
	pile_a[++pile_a[0]] = god->extremities[1]->id;
	while (pile_a[0] || pile_b[0])
	{
		if (depth % 2)
			ft_execute_pile_end_to_start(god, depth, pile_a, pile_b);
		else
			ft_execute_pile_end_to_start(god, depth, pile_b, pile_a);
		depth++;
	}
	ft_memdel((void**)&pile_a);
	ft_memdel((void**)&pile_b);
}

//+1 to depth if normal
//dont allow norml if daddy
//daddy use is -1 depth

// int 			update_dist

int				are_these_room_correctly_oriented(t_lemin *from, t_lemin *to)
{
	if ((from->orientation < to->orientation))
		return (1);
	return (0);
}

int				is_this_extremities(t_god *god, t_lemin *here)
{
	if (here->id == god->extremities[0]->id
	|| here->id == god->extremities[1]->id)
		return (1);
	return (0);

}

void			get_dist_from_end_oriented_graph(t_god *god)
{
	t_lemin 	*here;
	int			action;
	int			i;
	int			j;

	i = -1;
	action = 1;
	god->extremities[1]->dist_to_end = 0;
	while (action)
	{
		action = 0;
		while (++i < god->size)
		{
			here = god->rooms[i];
			if (is_this_extremities(god, here))
				continue;
			if (here->dist_to_end != INT_MAX)
			{
				if (here->last_room)
				{
					if (here->last_room->dist_to_end > here->dist_to_end - 1 && ++action)
						here->last_room->dist_to_end = here->dist_to_end - 1;
				}
				else
				{
					j = -1;
					while (here->connexions[++j])
						if (are_these_room_correctly_oriented(here, here->connexions[j]))
							if (here->connexions[j]->dist_to_end > here->dist_to_end + 1 && ++action)
								here->connexions[j]->dist_to_end = here->dist_to_end + 1;
				}
			}
			else
				action++;
		}
	}
}

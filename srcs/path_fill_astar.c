/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fill_astar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:05:17 by root              #+#    #+#             */
/*   Updated: 2019/06/18 15:34:36 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				execute_pile(t_god *god, int depth, int *pile_a, int *pile_b, int id_end, int start_to_end)
{
		t_lemin		*lem_in;
		int				*a;
		int				*b;
		int				i;
		int				r_v;

		a = &pile_a[0];
		b = &pile_b[0];
		r_v = 0;
		while (*a > 0)
		{
			lem_in = god->rooms[pile_a[*a]];
			if (!lem_in || lem_in->gone)
			{
				pile_a[(*a)--] = 0;
				continue;
			}
			if (lem_in->id == id_end)
			{
				r_v++;
				// lem_in->from[start_to_end] = depth;
			}
			if (!lem_in->from[start_to_end]) // 0 is start to end
			{
				lem_in->from[start_to_end] = depth;
				i = -1;
				while (lem_in->connexions[++i])
						pile_b[++(*b)] = ((t_lemin*)lem_in->connexions[i])->id;
			}
			pile_a[(*a)--] = 0;
		}
		return (r_v);
}

int				alternate_piles(t_god *god, int id_start, int id_end, int start_to_end)
{
	int		*pile_a;
	int		*pile_b;
	int 	depth;
	int		r_v;
	// int		i;

	depth = 0;
	pile_a = ft_memalloc(sizeof(int) * god->size * 2);
	pile_b = ft_memalloc(sizeof(int) * god->size * 2);
	pile_a[0] = 1;
	pile_a[1] = id_start;
	r_v = 0;
	while (pile_a[0] || pile_b[0])
	{
		if (depth % 2)
			r_v += execute_pile(god, depth, pile_a, pile_b, id_end, start_to_end);
		else
			r_v += execute_pile(god, depth, pile_b, pile_a, id_end, start_to_end);
		depth++;
	}
	ft_memdel((void**)&pile_a);
	ft_memdel((void**)&pile_b);
	return (r_v);
}

int				refresh_a_star(t_god *god)
{
	int r_v;

	r_v = 0;
	clear_data(god);
	// r_v = alternate_piles(god, god->start->id, god->end->id, 0);
	// god->start->from[0] = 0;
	r_v = alternate_piles(god, god->end->id, god->start->id, 1);
	god->end->from[1] = 0;
	return (r_v);
}

// int				from_start(t_lemin *lem_in, int depth)
// {
// 		int				i;
// 		int				r_v;
//
// 		r_v = 0;
// 		if (!lem_in || lem_in->gone)
// 			return (0);
// 		if (!lem_in->from[0] || lem_in->from[0] > depth)
// 		{
// 			lem_in->from[0] = depth;
// 			i = -1;
// 			while (lem_in->connexions[++i])
// 				r_v += from_start(lem_in->connexions[i], depth + 1);
// 		}
// 		return (r_v);
// }
//
// int				from_end(t_lemin *lem_in, int depth)
// {
// 		int				i;
// 		int				r_v;
//
// 		r_v = 0;
// 		if (!lem_in || lem_in->gone)
// 			return (0);
// 		if (!lem_in->from[1] || lem_in->from[1] > depth)
// 		{
// 				lem_in->from[1] = depth;
// 			i = -1;
// 			while (lem_in->connexions[++i])
// 				r_v += from_end(lem_in->connexions[i], depth + 1);
// 		}
// 		return (r_v);
// }

int			is_there_a_path(t_god *god, int *kill_list, int point_a, int point_b)
{
	int r_v;
	int	i;

	r_v = 0;
	clear_data(god);
	i = -1;
	if (kill_list)
		kill_list = NULL;
	// while (++i < kill_list[0])
		// god->rooms[kill_list[i]]->gone = 1;
	god->end->gone = 1;
	god->start->gone = 1;
	r_v = alternate_piles(god, god->rooms[point_a]->id, god->rooms[point_b]->id, 0);
	god->end->gone = 0;
	god->start->gone = 0;
	i = -1;
	i++;
	// while (++i < kill_list[0])
	// 	god->rooms[kill_list[i]]->gone = 0;
	clear_data(god);
	return (r_v);
}

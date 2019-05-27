/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_a_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:05:17 by root              #+#    #+#             */
/*   Updated: 2019/05/27 18:04:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				from_start(t_lemin *lem_in, int depth)
{
		int				i;
		int				r_v;

		r_v = 0;
		if (!lem_in || lem_in->gone)
			return (0);
		if (!lem_in->from_start || lem_in->from_start > depth)
		{
			lem_in->from_start = depth;
			i = -1;
			while (lem_in->connexions[++i])
				r_v += from_start(lem_in->connexions[i], depth + 1);
		}
		return (r_v);
}

int				from_end(t_lemin *lem_in, int depth)
{
		int				i;
		int				r_v;

		r_v = 0;
		if (!lem_in || lem_in->gone)
			return (0);
		if (!lem_in->from_end || lem_in->from_end > depth)
		{
				lem_in->from_end = depth;
			i = -1;
			while (lem_in->connexions[++i])
				r_v += from_end(lem_in->connexions[i], depth + 1);
		}
		return (r_v);
}

int				refresh_a_star(t_god *god)
{
	from_start(god->start, 0);
	god->start->from_start = 0;
	from_end(god->end, 0);
	god->end->from_end = 0;
	return (1);
}

/*
int				go_depth_first(t_lemin *lem_in, int (*f)(t_lemin *, t_lemin *, int, int), int depth)
{
		void			***tab;
		int				i;
		int				r_v;

		if (f(lem_in, NULL, 0, depth))
		{
			if ((r_v = f(lem_in, NULL, 0, depth)) != -1)
				return (r_v);
			else
				r_v = 0;
			tab = get_data_in_tab(lem_in, );
			order_data(tab, );
			i = -1;
			while (tab[++i][0])
				if (r_v = go_depth_first(tab[i][0], depth + 1))// while r_v = 0, continue to explore
					return (r_v);
		}
		return (r_v);
}

void				***get_data_in_tab(t_lemin *lem_in, (void*) (*f)(t_lemin *, int))
{
	void			***tab;
	int				size;
	int				values;
	int				j;
	int				i;

	size = 0;
	while (lem_in->connexions[size])
		size++;
	tab = ft_memalloc((sizeof(void*) * size);
	i = -1;
	values = (int)f(NULL, 0);
	while (++i < size)
	{
		tab[i] = ft_memalloc((sizeof(void*) * (values + 1)) + 1);
		tab[i][0] = lem_in->connexions[i];
		j = 0;
		while (++j <= values)
			tab[i][j] = f(lem_in->connexions[i], j);
	}
	return (tab);
}

int				find_shortest_path_to_end(t_lemin *lem_one, t_lemin *lem_two, int val, int mode)
{
	if (mode == 0) //going inside recursive condition
	{
		if (!lem_one->from_start || lem_one->from_start > val)
			return (1);
		return (0);
	}
	else if (mode == 1) //Pre work and stay in if r_v = -1;
	{
		if (!lem_one)
			return (0);
		if (!lem_one->gone)
			lem_one->from_start = depth;
		else
		{
			lem_one->from_start = 10000000;
			return (0);
		}
		if (lem_in->place == 1)
			return (1);
		return (-1);
	}
}
*/

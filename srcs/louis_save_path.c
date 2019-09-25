/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_save_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:41:34 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/25 17:09:11 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_ints	*malloc_paths(t_god *god)
{
	t_ints			*malloc_paths;
	int				i;

	malloc_paths = ft_memalloc(sizeof(t_ints) * (god->goulots + 1));
	i = -1;
	while (++i <= god->goulots)
		malloc_paths[i] = ft_memalloc(sizeof(int) * god->size * 2);
	return (malloc_paths);
}

int		write_path(t_god *god, t_lemin *here, t_ints path)
{
	int				r_v;

	r_v = FAILURE;
	if (here)
	{
		r_v = SUCCESS;
		if (here->id != god->extremities[0]->id)
			r_v = write_path(god, here->last_room, path);
		if (here->last_room)
			here->depth = here->last_room->depth + 1;
		else
			here->depth = 0;
		here->gone = 1;
		path[++path[0]] = here->id;
	}
	return (r_v);
}

void	save_solution(t_god *god, t_data *daddy)
{
	int				r_v;
	int				i;

	r_v = 0;
	if (god->used_goulots[0])
	{
		i = 0;
		while (++i <= god->used_goulots[0])
			if (god->used_goulots[i] == daddy->daddy->id)
				r_v++;
		if (!r_v)
			god->used_goulots[++god->used_goulots[0]] = daddy->daddy->id;
	}
	else
		god->used_goulots[++god->used_goulots[0]] = daddy->daddy->id;
	god->reach_end_room = daddy;
}

void	block_path_connections(t_god *god, t_ints path)
{
	int				check;
	int				i;

	i = 0;
	if (path)
		while (++i <= path[0] - 1)
			if ((check = find_connec_id(god, path[i], path[i + 1])) >= 0)
				god->rooms[path[i]]->used[check] = 1;
}

void	extract_paths(t_god *god)
{
	t_ints			*path;
	int				i;
	int				turn;

	i = 0;
	path = malloc_paths(god);
	while (++i <= god->used_goulots[0])
	{
		write_path(god, god->rooms[god->used_goulots[i]], path[i - 1]);
		path[i - 1][++path[i - 1][0]] = god->extremities[1]->id;
		block_path_connections(god, path[i - 1]);
		path[i - 1][0]--;
	}
	god->paths = path;
	god->nb_of_paths = god->used_goulots[0];
	turn = evaluate_set_of_path(god, god->paths, god->nb_of_paths);
	if (!god->final_path || turn < god->turn)
	{
		god->final_path = god->paths;
		god->nb_final_paths = god->nb_of_paths;
		god->turn = turn;
	}
}

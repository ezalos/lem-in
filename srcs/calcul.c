/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/06/01 21:20:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/head.h"

void 		clear_data(t_god *god)
{
		int i;

		i = -1;
		while (++i < god->size)
		{
			god->rooms[i]->from[1] = 0;
			god->rooms[i]->from[0] = 0;
		}
		god->start->gone = 0;
		god->end->gone = 0;
}

void 		clear_gone(t_god *god)
{
		int i;

		i = -1;
		while (++i < god->size)
			god->rooms[i]->gone = 0;
}

void 		add_gone_from_paths(t_god *god)
{
	t_path 	*path;
	int 		i;
	int			j;

	i = -1;
	while (++i < god->goulots)
	{
		path = &god->paths[i];
		if (path && path->path && path->path[0])
		{
			j = 0;
			while (++j <= path->path[0])
				god->rooms[path->path[j]]->gone = 1;
		}
	}
}

int				full_process(t_god *god, t_path *ptr)
{
	int		r_v;
	// ft_printf("%s\n", __func__);
	clear_data(god);
	r_v = refresh_a_star(god);
	// print_name_and_from_dist(god);
	if (r_v)
	{
		find_a_path(god->start, ptr);
		clear_data(god);
		return (1);
	}
	return (0);
}

int				get_rid_of_dead_ends(t_god *god)
{
	int i;
	int nb;
	int total;

	i = -1;
	nb = 1;
	total = 0;
	while (nb)
	{
		nb = 0;
		while (++i < god->size)
			if (god->rooms[i]->nb_of_connexions == 1 && !god->rooms[i]->place && ++nb)
				god->rooms[i]->connexions[0] = NULL;
		total += nb;
	}
	god->size -= total;
	ft_printf("Dead_ends_remover deleted %~{255;155;155}%d%~{} rooms\n", total);
	return (total);
}

void			does_path_exist(t_god *god, int a, int b)
{
	if (is_there_a_path(god, NULL, a, b))
		ft_printf("%~{155;255;155}");
	else
		ft_printf("%~{255;155;155}");
	ft_printf("%d-%d%~{}\n", a, b);
}

int				lets_calcul(t_god *god)
{
	int	i;
	int	missing_paths;

	// get_rid_of_dead_ends(god);
	how_many_entries_exits(god);
	if (!god->goulots)
	{
		ft_printf("%~{255;155;155}This Lem_in map does not have any solution%~{}\n");
		return (0);
	}
	god->paths = ft_memalloc(sizeof(t_path) * god->goulots);
	// does_path_exist(god, 39, 97);
	ft_printf("This anthill has %d rooms\n\n", god->size);
	i = -1;
	missing_paths = god->goulots;
	clear_gone(god);
	while (++i < god->goulots)
		missing_paths -= full_process(god, &god->paths[i]);
	print_paths(god);
	if (missing_paths)
		complete_missing_paths(god, missing_paths);
	return (0);
}

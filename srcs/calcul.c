/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/06/01 14:16:20 by root             ###   ########.fr       */
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
	// ft_printf("%s\n", __func__);
	// print_name_and_from_dist(god);
	if (refresh_a_star(god))
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

int				complete_missing_paths(t_god *god, int missing_paths)
{
		int	i;
		int	j;
		int smallest;
		t_path *the_choosen_two;

		ft_printf("Missing paths : %d/%d\n", missing_paths, god->goulots);
		i = -1;
		smallest = god->size;
		while (++i < god->goulots - missing_paths)
			if (ft_printf("Size of path %d is %d\n", i, god->paths[i].path[0]) && god->paths[i].path[0] < smallest)
				smallest = i;
		ft_printf("Smallest path is the n*%d:\n", smallest);
		print_this_path(god, &god->paths[smallest]);
		ft_printf("\n\nLets try to block room by room this path\n");
		i = 1;
		while (++i < god->paths[smallest].path[0])
		{
			the_choosen_two = ft_memalloc(sizeof(t_path));
			clear_gone(god);
			god->rooms[god->paths[smallest].path[i]]->gone = 1;
			if (god->size > 15)
			{
				j = 0;
				while (++j < god->exit_points)
				{
					god->rooms[god->exit_list[j]]->gone = 1;
					ft_printf("We just block room n* %d\n", god->exit_list[j]);
				}
			}
			ft_printf("We just block room n* %d\n", god->paths[smallest].path[i]);
			full_process(god, the_choosen_two);
			print_this_path(god, the_choosen_two);
			ft_memdel((void**)&the_choosen_two);
		}
		ft_printf("\n\nI hope there was a solution here...\n\n\n\n");
		return (0);
}

int				lets_calcul(t_god *god)
{
	int	i;
	int	missing_paths;

	get_rid_of_dead_ends(god);
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
	while (++i < god->goulots)
		missing_paths -= full_process(god, &god->paths[i]);
	if (missing_paths)
		complete_missing_paths(god, missing_paths);
	print_paths(god);
	return (0);
}

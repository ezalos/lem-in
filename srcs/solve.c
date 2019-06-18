/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/06/19 00:38:24 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				full_process(t_god *god, t_ints ptr)
{
	int		r_v;
	clear_data(god);
	r_v = refresh_a_star(god);
	// ft_printf("%s\n", __func__);
	// print_name_and_from_dist(god);
	if (r_v)
	{
		// ft_printf("%s\n", __func__);
		find_a_path(god->start, god->end->id, ptr);
		// ft_printf("%s\n", __func__);
		clear_data(god);
		print_this_path(god, ptr);
		return (1);
	}
	return (0);
}

void			does_path_exist(t_god *god, int a, int b)
{
	if (is_there_a_path(god, NULL, a, b))
		ft_printf("%~{155;255;155}");
	else
		ft_printf("%~{255;155;155}");
	ft_printf("%d-%d%~{}\n", a, b);
}

void 			init_paths(t_god *god)
{
	int	i;

	god->paths = ft_memalloc(sizeof(t_ints) * god->goulots);
	i = -1;
	while (++i < god->goulots)
		god->paths[i] = ft_memalloc(sizeof(int) * god->size);
}

int				lets_calcul(t_god *god)
{
	int	i;
	int	missing_paths;

	print_room_infos(god);
	how_many_entries_exits(god);
	if (!god->goulots && ft_printf("%~{255;155;155}There is no solution%~{}\n"))
		return (0);
	init_paths(god);
	missing_paths = god->goulots;
	i = -1;
	while (++i < god->goulots)
		missing_paths -= full_process(god, god->paths[i]);
	if (missing_paths)
		complete_missing_paths(god, missing_paths);
	return (0);
}

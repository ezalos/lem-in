/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/06/18 18:56:42 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				full_process(t_god *god, t_path *ptr)
{
	int		r_v;
	// ft_printf("%s\n", __func__);
	clear_data(god);
	r_v = refresh_a_star(god);
	// print_name_and_from_dist(god);
	if (r_v)
	{
		find_a_path(god->start, god->end->id, ptr);
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

int				lets_calcul(t_god *god)
{
	int	i;
	int	missing_paths;

	print_room_infos(god);
	how_many_entries_exits(god);
	if (!god->goulots && ft_printf("%~{255;155;155}There is no solution%~{}\n"))
		return (0);
	missing_paths = god->goulots;
	i = -1;
	while (++i < god->goulots)
		missing_paths -= full_process(god, &god->paths[i]);
	if (missing_paths)
		complete_missing_paths(god, missing_paths);
	return (0);
}

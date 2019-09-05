/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_follow_astar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:32:03 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:43:36 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		print_debug(t_lemin *here)
{
	if (here->place == START)
		ft_printf("%~{255;155;155}");
	else	if (here->place == END)
		ft_printf("%~{155;255;155}");
	ft_printf("%d%~{}\n", here->id);
}

void		save_this_path(t_lemin *here, t_ints *path)
{
	if (!*path)
		*path = ft_memalloc(sizeof(int) * (*ft_remember_god())->size);
	(*path)[++(*path)[0]] = here->id;
}

int			compare_rooms(t_lemin *zero, t_lemin *one)
{
	if (one->from[1] < zero->from[1])
		return (1);
	return (0);
}

void			find_a_path(t_lemin *here, int id, t_ints *path)
{
	int							winner;
	int							i;

	time_exe(__func__);
	i = -1;
	winner = -1;
	save_this_path(here, path);
	while (here->connexions[++i] && winner < 0)
		if (!((t_lemin*)here->connexions[i])->gone)
			winner = i;
	if (winner == -1)
		return ;
	if (here->id == id)
		return ;
	i = winner;
	while (here->connexions[++i])
		if (!((t_lemin*)here->connexions[i])->gone)
			if (compare_rooms(here->connexions[winner],
			here->connexions[i]))
				winner = i;
	here->gone = 1;
	find_a_path(here->connexions[winner], id, path);
}

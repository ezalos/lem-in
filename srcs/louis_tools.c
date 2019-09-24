/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:13:37 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/24 18:19:32 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		clean_search(t_god *god)
{
	int						i;

	i = -1;
	while (++i < god->size)
		god->rooms[i]->search = 0;
}

void		clean_gone(t_god *god)
{
	int						i;

	i = -1;
	while (++i < god->size)
	{
		god->rooms[i]->gone = 0;
		god->rooms[i]->depth = -1;
	}
}

void		reset_all(t_god *god)
{
	int						i;

	i = -1;
	while (++i < god->size)
	{
		god->rooms[i]->last_room = 0;
		god->rooms[i]->gone = 0;
	}
	god->used_goulots = 0;
}

void		save_yoyo(t_god *god)
{
	god->save_path = god->final_path;
	god->save_path_nb = god->nb_final_paths;
	god->save_turn = god->turn;
}

int			find_connec_id(t_god *god, int from, int to)
{
	int						i;

	i = -1;
	while (++i < god->rooms[from]->nb_of_connexions)
		if (god->rooms[from]->connexions[i]->id == god->rooms[to]->id)
			return (i);
	return (-1);
}
